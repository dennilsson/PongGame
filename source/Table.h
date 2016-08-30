#pragma once

#include <SDL.h>
#include <vector>

#include "Graphics.h"
#include "Globals.h"
#include "GameObject.h"

const int LINE_HEIGHT = 40;
const int LINE_WIDTH = 10;
const int LINE_SPACE = 40;

class Table
{
public:
    Table();
    void Draw(Graphics *graphics);

private:
    int center;
    int num_dots;

    std::vector<SDL_Rect> screenObjects;
};