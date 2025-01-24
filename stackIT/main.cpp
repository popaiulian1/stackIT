#include <iostream>
#include "Game.h"

int main() {
	
    // init io
    IO mIO;
    if (mIO.InitGraph() != 0)
    {
        return -1;
    }

    int mScreenHeight = mIO.GetScreenHeight();

    // Create game
    auto mPieces = std::make_shared<Pieces>();
    auto mBoard = std::make_shared<Board>(mPieces, mScreenHeight);
    auto mGame = std::make_shared<Game>(mBoard, std::make_shared<IO>(mIO), mPieces, mScreenHeight);

    unsigned long mTime1 = glfwGetTime() * 1000;

    // Game loop
    while (!mIO.IsKeyDown(GLFW_KEY_ESCAPE)) {
        mIO.ClearScreen();
        mGame->DrawScene();
        mIO.UpdateScreen();

        int mKey = mIO.Pollkey();

        switch (mKey)
        {
            // Move to right.
        case GLFW_KEY_D:
            if (mBoard->IsPossibleMovement(mGame->GetPosX() + 1, mGame->GetPosY(), mGame->GetPiece(), mGame->GetRotation()))
            {
                mGame->SetPosX(mGame->GetPosX() + 1);
            }
            break;

            // Move to left.
        case GLFW_KEY_A:
            if (mBoard->IsPossibleMovement(mGame->GetPosX() - 1, mGame->GetPosY(), mGame->GetPiece(), mGame->GetRotation()))
            {
                mGame->SetPosX(mGame->GetPosX() - 1);
            }
            break;

            // Move down.
        case GLFW_KEY_S:
            if (mBoard->IsPossibleMovement(mGame->GetPosX(), mGame->GetPosY() + 1, mGame->GetPiece(), mGame->GetRotation()))
            {
                mGame->SetPosY(mGame->GetPosY() + 1);
            }
            break;

            // Pressing x will make the piece to fall directly to the ground, after which we store the piece and delete possible lines
            // after which we check if the game is over and decide to create a new piece if not.
        case GLFW_KEY_X:
            while (mBoard->IsPossibleMovement(mGame->GetPosX(), mGame->GetPosY(), mGame->GetPiece(), mGame->GetRotation()))
            {
                mGame->SetPosY(mGame->GetPosY() + 1);
            }
            mBoard->StorePiece(mGame->GetPosX(), mGame->GetPosY() - 1, mGame->GetPiece(), mGame->GetRotation());
            mBoard->DeletePossibleLines();
            if (mBoard->IsGameOver())
            {
                std::cout << "\n\n ======= Game Over! ======= \n\n";
                return 0;
            }
            mGame->CreateNewPiece();
            break;

            // Used to rotate the piece.
        case GLFW_KEY_Z:
            if (mBoard->IsPossibleMovement(mGame->GetPosX(), mGame->GetPosY(), mGame->GetPiece(), (mGame->GetRotation() + 1) % 4))
            {
                mGame->SetRotation((mGame->GetRotation() + 1) % 4);
            }
            break;
        }

        // Gravity works :(( -> Just when i thought i was out, they pull me back in
        unsigned long mTime2 = glfwGetTime() * 1000;

        if ((mTime2 - mTime1) > WAIT_TIME) {
            if (mBoard->IsPossibleMovement(mGame->GetPosX(), mGame->GetPosY() + 1, mGame->GetPiece(), mGame->GetRotation())) {
                mGame->SetPosY(mGame->GetPosY() + 1);
            }
            else {
                mBoard->StorePiece(mGame->GetPosX(), mGame->GetPosY(), mGame->GetPiece(), mGame->GetRotation());
                mBoard->DeletePossibleLines();
                if (mBoard->IsGameOver())
                {
                    std::cout << "\n\n ======= Game Over! ======= \n\n";
                    return 0;
                }
                mGame->CreateNewPiece();
            }

            // Update our time
            mTime1 = glfwGetTime() * 1000;
        }
    }

    return 0;
}