#pragma once
#include "PieceUtils.h"

class Pieces
{
public:

	// Basic getters for info about the pieces
	int GetBlockType(int pPiece, int pRotation, int pX, int pY);
	int GetXInitialPosition(int pPiece, int pRotation);
	int GetYInitialPosition(int pPiece, int pRotation);
};

