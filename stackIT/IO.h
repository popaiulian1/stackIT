#pragma once

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
	uint16_t GetScreenHeight() const;
	int8_t InitGraph();
	int16_t Pollkey();
	int16_t Getkey();
	int16_t IsKeyDown(int pKey);
	void UpdateScreen();

private:
	// Variables
	GLFWwindow* mWindow;
	uint16_t mScreenHeight;
	uint16_t mScreenWidth;

	// Methods
	void SetColor(IUtils::Color pColor);
};

