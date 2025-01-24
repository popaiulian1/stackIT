#pragma once

#include "Board.h"
#include "IO.h"
#include "Pieces.h"
#include <random>
#include <chrono>
#include <memory>

constexpr uint16_t WAIT_TIME = 700; // How much time until the piece falls down in milliseconds

class Game
{
public:
	// Constructors
	Game(std::shared_ptr<Board> board, std::shared_ptr<IO> io, std::shared_ptr<Pieces> pieces, int screenHeight);

	// Methods
	void DrawScene();
	void CreateNewPiece();
	
	// Getters
	int GetPosX() const;
	int GetPosY() const;
	int GetPiece() const;
	int GetRotation() const;

	int GetNextPosX() const;
	int GetNextPosY() const;
	int GetNextPiece() const;
	int GetNextRotation() const;

	// Setters
	void SetPosX(int pX);
	void SetPosY(int pY);
	void SetPiece(int pPiece);
	void SetRotation(int pRotation);

	void SetNextPosX(int pX);
	void SetNextPosY(int pY);
	void SetNextPiece(int pPiece);
	void SetNextRotation(int pRotation);

private:
	// Variables
	std::shared_ptr<Board> mBoard;
	std::shared_ptr<IO> mIO;
	std::shared_ptr<Pieces> mPieces;

	int mScreenHeight; // Screen height in pixels
	std::mt19937 mRandomGenerator; 

	int mPosX, mPosY; // Position of the piece that is falling down
	int mPiece, mRotation; // Type and rotation of the piece that is falling down

	int mNextPosX, mNextPosY; // Position of the next piece
	int mNextPiece, mNextRotation; // Type and rotation of the next piece

	// Methods
	void InitGame();
	void DrawPiece(int pX, int pY, int pPiece, int pRotation);
	void DrawBoard();
	int GetRand(int min, int max);
};

