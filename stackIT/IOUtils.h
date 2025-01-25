#pragma once
#include "glm.hpp"
#include <cstdint>

namespace IUtils {
	static enum class Color {
		BLACK,
		RED,
		GREEN,
		BLUE,
		CYAN,
		MAGENTA,
		YELLOW,
		WHITE,
		COLOR_MAX
	};

	struct Character {
		GLuint TextureID; 
		glm::ivec2 Size;
		glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
		GLuint Advance; // Offset to advance to next glyph
	};
}