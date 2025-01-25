#include "IO.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

IO::IO() : mWindow(nullptr), mScreenHeight(600), mScreenWidth(600) {}

IO::~IO()
{
	if (mWindow)
	{
		glfwDestroyWindow(mWindow);
	}
	glfwTerminate();
}

void IO::DrawRectangle(int pX1, int pY1, int pX2, int pY2, IUtils::Color pColor)
{
	SetColor(pColor);
	glBegin(GL_QUADS);
	glVertex2i(pX1, pY1);
	glVertex2i(pX2, pY1);
	glVertex2i(pX2, pY2);
	glVertex2i(pX1, pY2);
	glEnd();
}

void IO::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
}

int IO::GetScreenHeight() const
{
	return mScreenHeight;
}

int IO::InitGraph()
{
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	mWindow = glfwCreateWindow(mScreenWidth, mScreenHeight, "stackIT", nullptr, nullptr);

	if (!mWindow) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(mWindow);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	glViewport(0, 0, mScreenWidth, mScreenHeight);

	// Set up the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, mScreenWidth, mScreenHeight, 0, -1, 1);

	// Set up the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << " initialized" << std::endl;

	// Initialize FreeType
	if (FT_Init_FreeType(&mFT)) {
		std::cerr << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		return -1;
	}

	//LoadFont("../thirdparty/fonts/PixelAE-Bold.ttf");

	// Load background image
	LoadBackgroundImage("../thirdparty/assets/Purple_Nebula_01-1024x1024.png");

	return 0;
}

int IO::Pollkey()
{
	if (glfwWindowShouldClose(mWindow))
	{
		return GLFW_KEY_ESCAPE;
	}

	for (int16_t key = GLFW_KEY_SPACE; key <= GLFW_KEY_RIGHT; key++)
	{
		if (glfwGetKey(mWindow, key) == GLFW_PRESS)
		{
			return key;
		}
	}
	return -1;
}

int IO::Getkey()
{
	while (true) {
		int key = Pollkey();
		if (key != -1)
		{
			return key;
		}
	}
}

int IO::IsKeyDown(int pKey)
{
	return glfwGetKey(mWindow, pKey) == GLFW_PRESS;
}

void IO::UpdateScreen()
{
	glfwSwapBuffers(mWindow);
	glfwPollEvents();
}

void IO::RenderText(const std::string& pText, int pX, int pY, int pSize, IUtils::Color pColor)
{
	SetColor(pColor);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(textVAO);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = pText.begin(); c != pText.end(); c++)
	{
		IUtils::Character ch = mCharacters[*c];
		GLfloat xpos = pX + ch.Bearing.x * pSize;
		GLfloat ypos = pY - (ch.Size.y - ch.Bearing.y) * pSize;
		GLfloat w = ch.Size.x * pSize;
		GLfloat h = ch.Size.y * pSize;

		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};

		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);

		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, textVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		pX += (ch.Advance >> 6) * pSize; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void IO::RenderBackground()
{
	// Reset color -> fixes bug where the background color would be green/blue
	glColor3f(1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, backgroundTexture);

	// Calculate the aspect ratio of the image
	float imageAspectRatio = static_cast<float>(backgroundImageWidth) / backgroundImageHeight;
	float windowAspectRatio = static_cast<float>(mScreenWidth) / mScreenHeight;

	float renderWidth, renderHeight;
	if (windowAspectRatio > imageAspectRatio) {
		// Window is wider than the image
		renderHeight = mScreenHeight;
		renderWidth = renderHeight * imageAspectRatio;
	}
	else {
		// Window is taller than the image
		renderWidth = mScreenWidth;
		renderHeight = renderWidth / imageAspectRatio;
	}

	float xOffset = (mScreenWidth - renderWidth) / 2.0f;
	float yOffset = (mScreenHeight - renderHeight) / 2.0f;

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(xOffset, yOffset);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(xOffset + renderWidth, yOffset);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(xOffset + renderWidth, yOffset + renderHeight);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(xOffset, yOffset + renderHeight);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void IO::SetColor(IUtils::Color pColor)
{
	switch (pColor) {
	case IUtils::Color::RED:
		glColor3f(1.f, 0.f, 0.f);
		break;

	case IUtils::Color::GREEN:
		glColor3f(0.f, 1.f, 0.f);
		break;

	case IUtils::Color::BLUE:
		glColor3f(0.f, 0.f, 1.f);
		break;

	case IUtils::Color::CYAN:
		glColor3f(0.f, 1.f, 1.f);
		break;

	case IUtils::Color::MAGENTA:
		glColor3f(1.f, 0.f, 1.f);
		break;
		
	case IUtils::Color::YELLOW:
		glColor3f(1.f, 1.f, 0.f);
		break;

	case IUtils::Color::WHITE:
		glColor3f(1.f, 1.f, 1.f);
		break;

	case IUtils::Color::BLACK:
	default:
		glColor3f(0.f, 0.f, 0.f);
		break;
	}
}

void IO::LoadFont(const std::string& fontPath)
{
	if (FT_New_Face(mFT, fontPath.c_str(), 0, &mFace))
	{
		std::cerr << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return;
	}

	FT_Set_Pixel_Sizes(mFace, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

	for (GLubyte c = 0; c < 128; c++) {
		if (FT_Load_Char(mFace, c, FT_LOAD_RENDER)) // Load character glyph
		{
			std::cerr << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
			continue;
		}

		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			mFace->glyph->bitmap.width,
			mFace->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			mFace->glyph->bitmap.buffer
		);

		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Now store character for later use
		IUtils::Character character = {
			texture,
			glm::ivec2(mFace->glyph->bitmap.width, mFace->glyph->bitmap.rows),
			glm::ivec2(mFace->glyph->bitmap_left, mFace->glyph->bitmap_top),
			static_cast<GLuint>(mFace->glyph->advance.x)
		};
		mCharacters.insert(std::pair<GLchar, IUtils::Character>(c, character));
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	// Destroy FreeType once we're finished
	FT_Done_Face(mFace);
	FT_Done_FreeType(mFT);

	// Configure VAO/VBO for texture quads
	glGenVertexArrays(1, &textVAO);
	glGenBuffers(1, &textVBO);
	glBindVertexArray(textVAO);
	glBindBuffer(GL_ARRAY_BUFFER, textVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	std::cout << "Font loaded successfully" << std::endl;
}

void IO::LoadBackgroundImage(const std::string& imagePath)
{
	int width, height, nrChannels;
	unsigned char* data = stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);
	if (!data) {
		std::cerr << "ERROR::STB: Failed to load image" << std::endl;
		return;
	}

	backgroundImageWidth = width;
	backgroundImageHeight = height;

	GLenum format;
	if (nrChannels == 1)
	{
		format = GL_RED;
	}
	else if (nrChannels == 3)
	{
		format = GL_RGB; 
	}
	else if (nrChannels == 4) {
		format = GL_RGBA; 
	}
	else {
		std::cerr << "ERROR::STB: Unsupported number of channels" << std::endl;
		stbi_image_free(data);
		return;
	}

	glGenTextures(1, &backgroundTexture);
	glBindTexture(GL_TEXTURE_2D, backgroundTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);
}
