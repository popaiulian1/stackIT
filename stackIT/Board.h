#pragma once

#include "Pieces.h"
#include "BoardUtils.h"
#include <memory>

namespace stackIT {

	class Board
	{
	public:
		Board(std::shared_ptr<Pieces> pPieces, int16_t pScreenHeight);
	};
}
