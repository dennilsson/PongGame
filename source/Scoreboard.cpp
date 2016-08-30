#include "Scoreboard.h"


Scoreboard::Scoreboard()
{
    leftScore = 0;
    rightScore = 0;

    leftPosX = (SCREEN_WIDTH / 2) - 50;
    leftPosY = 30;

    rightPosX = SCREEN_WIDTH / 2 + 50;
    rightPosY = 30;
}


void Scoreboard::AddScore(Score paddle)
{
    if (paddle == LEFT_PADDLE)
    {
        leftScore++;

        SDL_Rect rect = { leftPosX, leftPosY, 20, 20 };
        screenObjects.push_back(rect);

        // Make some screenspace for the next object
        leftPosX -= 40;
    }
    else if (paddle == RIGHT_PADDLE)
    {
        rightScore++;

        SDL_Rect rect = { rightPosX, rightPosY, 20, 20 };
        screenObjects.push_back(rect);

        // Make some screenspace for the next object
        rightPosX += 40;
    }
}


int Scoreboard::GetScore(Score paddle)
{
    if (paddle == LEFT_PADDLE)
    {
        return leftScore;
    }
    else if (paddle == RIGHT_PADDLE)
    {
        return rightScore;
    }

    return -1;
}


void Scoreboard::Draw(Graphics *graphics)
{
    for (auto &i : screenObjects)
    {
        graphics->Render(&i);
    }
}


void Scoreboard::Reset()
{
    leftScore = 0;
    rightScore = 0;

    leftPosX = (SCREEN_WIDTH / 2) - 50;
    rightPosX = SCREEN_WIDTH / 2 + 50;

    screenObjects.clear();
}