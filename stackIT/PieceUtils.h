#pragma once

namespace PieceUtils
{
	// These are the pieces that will be used in the game
	static char mPieces[7/* type */][4 /* rotation */][5 /* horizontals */][5 /* verticals */] = {
		// Square
		{
		{
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 2, 1, 0},
		{0, 0, 1, 1, 0},
		{0, 0, 0, 0, 0}
		},
		{
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 2, 1, 0},
		{0, 0, 1, 1, 0},
		{0, 0, 0, 0, 0}
		},
		{
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 2, 1, 0},
		{0, 0, 1, 1, 0},
		{0, 0, 0, 0, 0}
		},
		{
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 2, 1, 0},
		{0, 0, 1, 1, 0},
		{0, 0, 0, 0, 0}
		}
		},

		// I
		{
		{
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 1, 2, 1, 1},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
		},
		{
		{0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 2, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0}
		},
		{
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{1, 1, 2, 1, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
		},
		{
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 2, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0}
		}
		},

		// L
		{
		{
		{0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 2, 0, 0},
		{0, 0, 1, 1, 0},
		{0, 0, 0, 0, 0}
		},
		{
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 1, 2, 1, 0},
		{0, 1, 0, 0, 0},
		{0, 0, 0, 0, 0}
		},
		{
		{0, 0, 0, 0, 0},
		{0, 1, 1, 0, 0},
		{0, 0, 2, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0}
		},
		{
		{0, 0, 0, 0, 0},
		{0, 0, 0, 1, 0},
		{0, 1, 2, 1, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
		}
		},

		// L mirrored
		{
		{
		{0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 2, 0, 0},
		{0, 1, 1, 0, 0},
		{0, 0, 0, 0, 0}
		},
		{
		{0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0},
		{0, 1, 2, 1, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
		},
		{
		{0, 0, 0, 0, 0},
		{0, 0, 1, 1, 0},
		{0, 0, 2, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0}
		},
		{
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 1, 2, 1, 0},
		{0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0}
		}
		},

		// N
		{
		{
		{0, 0, 0, 0, 0},
		{0, 0, 0, 1, 0},
		{0, 0, 2, 1, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0}
		},
		{
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 1, 2, 0, 0},
		{0, 0, 1, 1, 0},
		{0, 0, 0, 0, 0}
		},
		{
		{0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 1, 2, 0, 0},
		{0, 1, 0, 0, 0},
		{0, 0, 0, 0, 0}
		},

		{
		{0, 0, 0, 0, 0},
		{0, 1, 1, 0, 0},
		{0, 0, 2, 1, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
		}
		},

		// N mirrored
		{
		{
		{0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 2, 1, 0},
		{0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0}
		},
		{
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 2, 1, 0},
		{0, 1, 1, 0, 0},
		{0, 0, 0, 0, 0}
		},
		{
		{0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0},
		{0, 1, 2, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0}
		},
		{
		{0, 0, 0, 0, 0},
		{0, 0, 1, 1, 0},
		{0, 1, 2, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
		}
		},

		// T
		{
		{
		{0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 2, 1, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0}
		},
		{
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 1, 2, 1, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0}
		},
		{
		{0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 1, 2, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0}
		},
		{
		{0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 1, 2, 1, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
		}
		}
	};

	// The pieces are 5x5 matrixes to allow all rotations, we need to define initial positions where they will be draw on the board
	// so as to avoid the empty space in the matrix, rendering the pieces only from where they start.

	static int mPiecesInitialPositions[7/* type */][4 /* rotation */][2 /* x, y */] = {
		// Square
		{
		{-2, -3},
		{-2, -3},
		{-2, -3},
		{-2, -3}
		},

		// I
		{
		{-2, -2},
		{-2, -3},
		{-2, -2},
		{-2, -3}
		},

		// L
		{
		{-2, -3},
		{-2, -3},
		{-2, -3},
		{-2, -2}
		},

		// L mirrored
		{
		{-2, -3},
		{-2, -2},
		{-2, -3},
		{-2, -3}
		},

		// N
		{
		{-2, -3},
		{-2, -3},
		{-2, -3},
		{-2, -2}
		},

		// N mirrored
		{
		{-2, -3},
		{-2, -3},
		{-2, -3},
		{-2, -2}
		},

		// T
		{
		{-2, -3},
		{-2, -3},
		{-2, -3},
		{-2, -2}
		},

	};
}