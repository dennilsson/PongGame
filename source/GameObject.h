#pragma once

#include <SDL.h>

#include "Vector2.h"
#include "Graphics.h"

class GameObject
{
public:
    int GetX()
    {
        return screenObject.x;
    }

    int GetY()
    {
        return screenObject.y;
    }

    int GetWidth()
    {
        return screenObject.w;
    }

    int GetHeight()
    {
        return screenObject.h;
    }

    // The derived class need to implement this function
    virtual void Update() = 0;

    // The derived class need to implement this function
    virtual void Draw(Graphics *graphics) = 0;
protected:
    Vector2 position;
    Vector2 velocity;

    SDL_Rect screenObject;
};
