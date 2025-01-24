#include "Game.h"

Game::Game(std::shared_ptr<Board> board, std::shared_ptr<IO> io, std::shared_ptr<Pieces> pieces, int screenHeight) :
	mBoard(std::move(board)), mPieces(std::move(pieces)), mIO(std::move(io)), mScreenHeight(screenHeight),
	mRandomGenerator(std::chrono::system_clock::now().time_since_epoch().count())
{
	InitGame();
}

void Game::DrawScene()
{
	std::cout << "Drawing scene" << std::endl;
	DrawBoard();
	DrawPiece(mPosX, mPosY, mPiece, mRotation);
	DrawPiece(mNextPosX, mNextPosY, mNextPiece, mNextRotation);
}

void Game::CreateNewPiece()
{
	mPiece = mNextPiece;
	mRotation = mNextRotation;
	mPosX = (BoardInfo::BOARD_WIDTH / 2) + mPieces->GetXInitialPosition(mPiece, mRotation);
	mPosY = mPieces->GetYInitialPosition(mPiece, mRotation);

	mNextPiece = GetRand(0, 6);
	mNextRotation = GetRand(0, 3);
}

int Game::GetPosX() const { return mPosX; }

int Game::GetPosY() const { return mPosY; }

int Game::GetPiece() const { return mPiece; }

int Game::GetRotation() const { return mRotation; }

int Game::GetNextPosX() const { return mNextPosX; }

int Game::GetNextPosY() const { return mNextPosY; }

int Game::GetNextPiece() const { return mNextPiece; }

int Game::GetNextRotation() const { return mNextRotation; }

void Game::SetPosX(int pX)
{
	mPosX = pX;
}

void Game::SetPosY(int pY)
{
	mPosY = pY;
}

void Game::SetPiece(int pPiece)
{
	mPiece = pPiece;
}

void Game::SetRotation(int pRotation)
{
	mRotation = pRotation;
}

void Game::SetNextPosX(int pX)
{
	mNextPosX = pX;
}

void Game::SetNextPosY(int pY)
{
	mNextPosY = pY;
}

void Game::SetNextPiece(int pPiece)
{
	mNextPiece = pPiece;
}

void Game::SetNextRotation(int pRotation)
{
	mNextRotation = pRotation;
}

void Game::InitGame()
{
	// Init current piece
	mPiece = GetRand(0, 6);
	mRotation = GetRand(0, 3);
	mPosX = (BoardInfo::BOARD_WIDTH / 2) + mPieces->GetXInitialPosition(mPiece, mRotation);
	mPosY = mPieces->GetYInitialPosition(mPiece, mRotation);

	// Init next piece
	mNextPiece = GetRand(0, 6);
	mNextRotation = GetRand(0, 3);
	mNextPosX = BoardInfo::BOARD_WIDTH + 5;
	mNextPosY = 5;
}

void Game::DrawPiece(int pX, int pY, int pPiece, int pRotation)
{
	std::cout << "Drawing piece at (" << pX << ", " << pY << ")" << std::endl;
	for (size_t i = 0; i < BoardInfo::PIECE_BLOCKS; ++i)
	{
		for (size_t j = 0; j < BoardInfo::PIECE_BLOCKS; ++j)
		{
			int blockType = mPieces->GetBlockType(pPiece, pRotation, i, j);
			if (blockType != 0)
			{
				IUtils::Color color = (blockType == 1) ? IUtils::Color::GREEN : IUtils::Color::BLUE;
				mIO->DrawRectangle(
					mBoard->GetXPosInPixels(pX) + i * BoardInfo::BLOCK_SIZE,
					mBoard->GetYPosInPixels(pY) + j * BoardInfo::BLOCK_SIZE,
					mBoard->GetXPosInPixels(pX) + (i + 1) * BoardInfo::BLOCK_SIZE - 1,
					mBoard->GetYPosInPixels(pY) + (j + 1) * BoardInfo::BLOCK_SIZE - 1,
					color
				);
			}
		}
	}
}

void Game::DrawBoard()
{
	std::cout << "Drawing board" << std::endl;
	int x1 = BoardInfo::BOARD_POSITION - (BoardInfo::BLOCK_SIZE * (BoardInfo::BOARD_WIDTH / 2)) - 1;
	int x2 = BoardInfo::BOARD_POSITION + (BoardInfo::BLOCK_SIZE * (BoardInfo::BOARD_WIDTH / 2));
	int y = mScreenHeight - (BoardInfo::BLOCK_SIZE * BoardInfo::BOARD_HEIGHT);

	mIO->DrawRectangle(x1 - BoardInfo::BOARD_LINE_WIDTH, y, x1, mScreenHeight - 1, IUtils::Color::WHITE);
	mIO->DrawRectangle(x2, y, x2 + BoardInfo::BOARD_LINE_WIDTH, mScreenHeight - 1, IUtils::Color::WHITE);

	for (size_t i = 0; i < BoardInfo::BOARD_WIDTH; ++i) {
		for (size_t j = 0; j < BoardInfo::BOARD_HEIGHT; ++j) {
			if (!mBoard->IsFreeBlock(i, j)) {
				mIO->DrawRectangle(
					x1 + 1 + i * BoardInfo::BLOCK_SIZE,
					y + j * BoardInfo::BLOCK_SIZE,
					x1 + 1 + (i + 1) * BoardInfo::BLOCK_SIZE - 1,
					y + (j + 1) * BoardInfo::BLOCK_SIZE - 1,
					IUtils::Color::RED
				);
			}
		}
	}
}

int Game::GetRand(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(mRandomGenerator);
}
