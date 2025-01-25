#pragma once

#include "GL/glew.h"
#include "glfw3.h"
#include "ft2build.h"
#include FT_FREETYPE_H
#include "IOUtils.h"
#include <iostream>
#include <map>

class IO
{
public:
	// Constructors
	IO();
	~IO();

	// Methods
	void DrawRectangle(int pX1, int pY1, int pX2, int pY2, IUtils::Color pColor);
	void ClearScreen();
	int GetScreenHeight() const;
	int InitGraph();
	int Pollkey();
	int Getkey();
	int IsKeyDown(int pKey);
	void UpdateScreen();
	void RenderText(const std::string& pText, int pX, int pY, int pSize, IUtils::Color pColor);
	void RenderBackground();

private:
	// Variables
	GLFWwindow* mWindow;
	int mScreenHeight;
	int mScreenWidth;

	// === (TO DO) : implement the text rendering for scoring system ===
	FT_Library mFT;
	FT_Face mFace;
	GLuint textVAO, textVBO;
	std::map<char, IUtils::Character> mCharacters;

	GLuint backgroundTexture;
	int backgroundImageWidth;
	int backgroundImageHeight;

	// Methods
	void SetColor(IUtils::Color pColor);
	void LoadFont(const std::string& fontPath);
	void LoadBackgroundImage(const std::string& imagePath);
};

