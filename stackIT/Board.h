#pragma once

#include "Pieces.h"
#include "BoardUtils.h"
#include <memory>

namespace stackIT {

	class Board
	{
	public:
		// Constructors
		Board(std::shared_ptr<Pieces> pPieces, int16_t pScreenHeight);

		// Methods
		uint8_t GetXPosInPixels(uint8_t pPos);
		uint8_t GetYPosInPixels(uint8_t pPos);
		bool IsFreeBlock(uint8_t pX, uint8_t pY) const;
		bool IsPossibleMovement(uint8_t pX, uint8_t pY, uint8_t pPiece, uint8_t pRotation);
		void StorePiece(uint8_t pX, uint8_t pY, uint8_t pPiece, uint8_t pRotation);
		void DeletePossibleLines();
		bool IsGameOver() const;

	private:
		// Methods
		void InitBoard();
		void DeleteLine(int pY);

		// Variables
		int mBoard[BoardInfo::BOARD_WIDTH][BoardInfo::BOARD_HEIGHT];
		std::shared_ptr<Pieces> mPieces;
		int16_t mScreenHeight;
	};
}
