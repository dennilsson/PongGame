#pragma once

#include <SDL.h>
#include <random>

#include "Graphics.h"
#include "Globals.h"
#include "Vector2.h"
#include "GameObject.h"


const int BALL_HEIGHT = 20;
const int BALL_WIDTH = 20;
const int BALL_SPEED = 5;


class Ball : public GameObject
{
public:
    Ball();

    void Update();
    void Draw(Graphics *graphics);
    void ResetPosition();
    bool CheckCollision(GameObject &object);

private:
    Vector2 position;
    Vector2 velocity;

    // Generates a random number and returns it.
    int GetRandomPosition(int min_value, int max_value)
    {
        // Seed with a real random value, if available
        std::random_device rd;
         
        // Choose a random mean between min and max
        std::default_random_engine e1(rd());
        std::uniform_int_distribution<int> uniform_dist(min_value, max_value);
        int mean = uniform_dist(e1);

        return mean;
    }
};

