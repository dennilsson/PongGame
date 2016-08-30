#pragma once

#include <SDL.h>

#include "graphics.h"
#include "globals.h"
#include "GameObject.h"

const int PADDLE_HEIGHT = 120;
const int PADDLE_WIDTH = 20;
const int PADDLE_SPEED = 15;

class Paddle : public GameObject
{
public:
    Paddle(int x, int y);

    void Update();
	void Draw(Graphics *graphics);
    void MoveUp();
    void MoveDown();
    void StopMoving();
    void AddScore();
    int GetScore();

private:
    // default point for the player
    int score = 0;
};

