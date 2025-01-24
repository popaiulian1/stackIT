#include "IO.h"

IO::IO() : mWindow(nullptr), mScreenHeight(800), mScreenWidth(600) {}

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

uint16_t IO::GetScreenHeight() const
{
	return mScreenHeight;
}

int8_t IO::InitGraph()
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

	return 0;
}

int16_t IO::Pollkey()
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

int16_t IO::Getkey()
{
	while (true) {
		int16_t key = Pollkey();
		if (key != -1)
		{
			return key;
		}
	}
}

int16_t IO::IsKeyDown(int pKey)
{
	return glfwGetKey(mWindow, pKey) == GLFW_PRESS;
}

void IO::UpdateScreen()
{
	glfwSwapBuffers(mWindow);
	glfwPollEvents();
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
