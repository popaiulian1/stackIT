#pragma once
#include "PieceUtils.h"

class Pieces
{
public:
	// Basic getters for info about the pieces
	static int GetBlockType(int pPiece, int pRotation, int pX, int pY);
	static int GetXInitialPosition(int pPiece, int pRotation);
	static int GetYInitialPosition(int pPiece, int pRotation);
};

