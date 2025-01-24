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
	for (int j = pY; j > 0; j--)
	{
		for (int i = 0; i < BoardInfo::BOARD_WIDTH; i++)
		{
			mBoard[i][j] = mBoard[i][j - 1];
		}
	}
}

Board::Board(std::shared_ptr<Pieces> pPieces, int16_t pScreenHeight)
{
	mPieces = pPieces;
	mScreenHeight = pScreenHeight;
	InitBoard();
}

uint8_t Board::GetXPosInPixels(uint8_t pPos)
{
	return ((BoardInfo::BOARD_POSITION - (BoardInfo::BLOCK_SIZE * (BoardInfo::BOARD_WIDTH/2))) + (pPos * BoardInfo::BLOCK_SIZE));
}

uint8_t Board::GetYPosInPixels(uint8_t pPos)
{
	return ((mScreenHeight - (BoardInfo::BLOCK_SIZE * BoardInfo::BOARD_HEIGHT)) + (pPos * BoardInfo::BLOCK_SIZE));
}

bool Board::IsFreeBlock(uint8_t pX, uint8_t pY) const
{
	return mBoard[pX][pY] == static_cast<int>(BoardInfo::PosStatus::POS_FREE);
}

bool Board::IsPossibleMovement(uint8_t pX, uint8_t pY, uint8_t pPiece, uint8_t pRotation) const
{
	// Check collision with pieces already stored in the board or the board limits
	for (size_t i = pX, x = 0; i < pX + BoardInfo::PIECE_BLOCKS; i++, x++)
	{
		for (size_t j = pY, y = 0; j < pY + BoardInfo::PIECE_BLOCKS; j++, y++)
		{
			// Check if the piece is outside the limits of the board
			if (i < 0 || i > BoardInfo::BOARD_WIDTH - 1 || j > BoardInfo::BOARD_HEIGHT - 1)
			{
				if (Pieces::GetBlockType(pPiece, pRotation, x, y) != 0)
				{
					return false;
				}
			}
			// Check if the piece have collisioned with a block already stored in the map
			if (j >= 0)
			{
				if (Pieces::GetBlockType(pPiece, pRotation, x, y) != 0 && !IsFreeBlock(i, j))
				{
					return false;
				}
			}
		}
	}
	return true;
}

void Board::StorePiece(uint8_t pX, uint8_t pY, uint8_t pPiece, uint8_t pRotation)
{
	for (size_t i = pX, x = 0; i < pX + BoardInfo::PIECE_BLOCKS; i++, x++)
	{
		for (size_t j = pY, y = 0; j < pY + BoardInfo::PIECE_BLOCKS; j++, y++)
		{
			if (Pieces::GetBlockType(pPiece, pRotation, x, y) != 0)
			{
				mBoard[i][j] = static_cast<int>(BoardInfo::PosStatus::POS_FILLED);
			}
		}
	}
}

void Board::DeletePossibleLines()
{
	for (size_t i = 0; i < BoardInfo::BOARD_HEIGHT; i++) {

		size_t j = 0;

		while (j < BoardInfo::BOARD_WIDTH)
		{
			// check if the line is filled
			if (mBoard[j][i] != static_cast<int>(BoardInfo::PosStatus::POS_FILLED))
			{
				break;
			}
			j++;
		}
		// if j is equal to BOARD_WIDTH, the line is filled and needs to be deleted
		if (j == BoardInfo::BOARD_WIDTH)
		{
			DeleteLine(i);
		}
	}
}

bool Board::IsGameOver() const
{
	for (size_t i = 0; i < BoardInfo::BOARD_WIDTH; i++)
	{
		if (mBoard[i][0] == static_cast<int>(BoardInfo::PosStatus::POS_FILLED))
		{
			return true;
		}
	}
	return false;
}
