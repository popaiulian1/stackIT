#pragma once

#include "Pieces.h"
#include "BoardUtils.h"
#include <memory>

class Board
{
public:
	// Constructors
	Board(std::shared_ptr<Pieces> pPieces, int pScreenHeight);

	// Methods
	int GetXPosInPixels(int pPos);
	int GetYPosInPixels(int pPos);
	bool IsFreeBlock(int pX, int pY) const;
	bool IsPossibleMovement(int pX, int pY, int pPiece, int pRotation) const;
	void StorePiece(int pX, int pY, int pPiece, int pRotation);
	void DeletePossibleLines();
	bool IsGameOver() const;

private:
	// Variables
	int mBoard[BoardInfo::BOARD_WIDTH][BoardInfo::BOARD_HEIGHT];
	std::shared_ptr<Pieces> mPieces;
	int mScreenHeight;

	// Methods
	void InitBoard();
	void DeleteLine(int pY);
};
