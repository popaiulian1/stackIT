#pragma once

#include <cstdint>

namespace BoardInfo {

	// Board constants
	constexpr uint8_t BOARD_WIDTH = 10; // board width in blocks
	constexpr uint8_t BOARD_HEIGHT = 20; // board height in blocks
	constexpr uint8_t BLOCK_SIZE = 16; // size of the blocks of the pieces (width & height)
	constexpr uint8_t BOARD_LINE_WIDTH = 6; // size of the board frame
	constexpr uint8_t BOARD_POSITION = 320; // center pos from left side of the screen
	constexpr uint8_t MIN_VERTICAL_MARGIN = 20; // minimum vertical margin for the board limit
	constexpr uint8_t MIN_HORIZONTAL_MARGIN = 20; // minimum horizontal margin for the board limit
	constexpr uint8_t PIECE_BLOCKS = 5; // number of horizontal and vertical blocks of a matrix piece

	enum class PosStatus {
		POS_FREE, // free position
		POS_FILLED, // filled position
	};
}