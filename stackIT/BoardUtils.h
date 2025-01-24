#pragma once

#include <cstdint>

namespace BoardInfo {

	// Board constants
	constexpr int BOARD_WIDTH = 10; // board width in blocks
	constexpr int BOARD_HEIGHT = 20; // board height in blocks
	constexpr int BLOCK_SIZE = 16; // size of the blocks of the pieces (width & height)
	constexpr int BOARD_LINE_WIDTH = 6; // size of the board frame
	constexpr int BOARD_POSITION = 350; // center pos from left side of the screen
	constexpr int MIN_VERTICAL_MARGIN = 20; // minimum vertical margin for the board limit
	constexpr int MIN_HORIZONTAL_MARGIN = 20; // minimum horizontal margin for the board limit
	constexpr int PIECE_BLOCKS = 5; // number of horizontal and vertical blocks of a matrix piece

	static enum class PosStatus {
		POS_FREE, // free position
		POS_FILLED, // filled position
	};
}