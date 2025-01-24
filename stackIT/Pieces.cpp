#include "Pieces.h"

// Returns the type of the block at the piece's position ( 0 = no block, 1 = normal block, 2 = pivot block)
int Pieces::GetBlockType(int pPiece, int pRotation, int pX, int pY)
{
	return PieceUtils::pieces[pPiece][pRotation][pX][pY];
}

// Returns the X displacement of the piece
int Pieces::GetXInitialPosition(int pPiece, int pRotation)
{
	return PieceUtils::piecesInitialPositions[pPiece][pRotation][0];
}

// Returns the Y displacement of the piece
int Pieces::GetYInitialPosition(int pPiece, int pRotation)
{
	return PieceUtils::piecesInitialPositions[pPiece][pRotation][1];
}
