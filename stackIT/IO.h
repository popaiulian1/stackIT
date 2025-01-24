#pragma once

#include "GL/glew.h"
#include "glfw3.h"
#include "IOUtils.h"
#include <iostream>

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

private:
	// Variables
	GLFWwindow* mWindow;
	int mScreenHeight;
	int mScreenWidth;

	// Methods
	void SetColor(IUtils::Color pColor);
};

