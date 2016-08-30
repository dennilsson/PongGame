#pragma once

#include <vector>

#include "Graphics.h"
#include "Globals.h"

enum Score
{
    LEFT_PADDLE,
    RIGHT_PADDLE
};


class Scoreboard
{
public:
    Scoreboard();

    void AddScore(Score paddle);
    int GetScore(Score paddle);
    void Draw(Graphics *graphics);
    void Reset();

private:
    int leftScore;
    int rightScore;

    int leftPosX;
    int leftPosY;

    int rightPosX;
    int rightPosY;


    std::vector<SDL_Rect> screenObjects;

    int y;
};

