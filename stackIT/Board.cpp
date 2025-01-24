#include "Board.h"

void Board::InitBoard()
{
	for (int i = 0; i < BoardInfo::BOARD_WIDTH; i++) {
		for (int j = 0; j < BoardInfo::BOARD_HEIGHT; j++)
		{
			mBoard[i][j] = static_cast<int>(BoardInfo::PosStatus::POS_FREE);
		}
	}
}

void Board::DeleteLine(int pY)
{
	// Move all lines above the deleted line down by one
	for (int y = pY; y > 0; --y)
	{
		for (int x = 0; x < BoardInfo::BOARD_WIDTH; ++x)
		{
			mBoard[x][y] = mBoard[x][y - 1];
		}
	}

	// Clear the top line
	for (int x = 0; x < BoardInfo::BOARD_WIDTH; ++x)
	{
		mBoard[x][0] = static_cast<int>(BoardInfo::PosStatus::POS_FREE);
	}
}

Board::Board(std::shared_ptr<Pieces> pPieces, int pScreenHeight)
{
	mPieces = pPieces;
	mScreenHeight = pScreenHeight;
	InitBoard();
}

int Board::GetXPosInPixels(int pPos)
{
	return ((BoardInfo::BOARD_POSITION - (BoardInfo::BLOCK_SIZE * (BoardInfo::BOARD_WIDTH/2))) + (pPos * BoardInfo::BLOCK_SIZE));
}

int Board::GetYPosInPixels(int pPos)
{
	return ((mScreenHeight - (BoardInfo::BLOCK_SIZE * BoardInfo::BOARD_HEIGHT)) + (pPos * BoardInfo::BLOCK_SIZE));
}

bool Board::IsFreeBlock(int pX, int pY) const
{
	return mBoard[pX][pY] == static_cast<int>(BoardInfo::PosStatus::POS_FREE);
}

bool Board::IsPossibleMovement(int pX, int pY, int pPiece, int pRotation) const
{
	// Check collision with pieces already stored in the board or the board limits
	for (int i = 0; i < BoardInfo::PIECE_BLOCKS; ++i)
	{
		for (int j = 0; j < BoardInfo::PIECE_BLOCKS; ++j)
		{
			int blockType = Pieces::GetBlockType(pPiece, pRotation, i, j);
			if (blockType != 0)
			{
				int newX = pX + i;
				int newY = pY + j;

				// Check if the piece is outside the limits of the board
				if (newX < 0 || newX >= BoardInfo::BOARD_WIDTH || newY >= BoardInfo::BOARD_HEIGHT)
				{
					return false;
				}

				// Check if the piece has collided with a block already stored in the board
				if (newY >= 0 && !IsFreeBlock(newX, newY))
				{
					return false;
				}
			}
		}
	}
	return true;
}

void Board::StorePiece(int pX, int pY, int pPiece, int pRotation)
{
	for (int i = 0; i < BoardInfo::PIECE_BLOCKS; ++i)
	{
		for (int j = 0; j < BoardInfo::PIECE_BLOCKS; ++j)
		{
			int blockType = Pieces::GetBlockType(pPiece, pRotation, i, j);
			if (blockType != 0)
			{
				mBoard[pX + i][pY + j] = blockType;
			}
		}
	}
}

void Board::DeletePossibleLines()
{
	for (int y = 0; y < BoardInfo::BOARD_HEIGHT; ++y)
	{
		bool lineComplete = true;

		// Check if the line is complete
		for (int x = 0; x < BoardInfo::BOARD_WIDTH; ++x)
		{
			if (mBoard[x][y] == static_cast<int>(BoardInfo::PosStatus::POS_FREE))
			{
				lineComplete = false;
				break;
			}
		}

		// If the line is complete, delete it
		if (lineComplete)
		{
			DeleteLine(y);
		}
	}
}

bool Board::IsGameOver() const
{
	for (int i = 0; i < BoardInfo::BOARD_WIDTH; i++)
	{
		if (mBoard[i][0] == static_cast<int>(BoardInfo::PosStatus::POS_FILLED))
		{
			return true;
		}
	}
	return false;
}
