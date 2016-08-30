#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cstdio>

#include "Globals.h"
#include "Graphics.h"
#include "InputHandler.h"
#include "Paddle.h"
#include "Ball.h"
#include "Table.h"
#include "Scoreboard.h"

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

enum GameState
{
    STATE_RUNNING,
    STATE_PAUSE,
    STATE_GAMEOVER
};

class Game
{
public:
    ~Game();

    bool Init();
    void RunFrame();
    void HandleInput();

    bool IsRunning()
    {
        return isRunning;
    }

private:
    SDL_Event sdl_event;
    SDL_Window *window;
    SDL_Surface *surface;

    Graphics *graphics;
    InputHandler *input;

    bool isRunning;

    int frameStart, frameTime;

    Table *table;
    Ball *ball;
    Paddle *paddle1;
    Paddle *paddle2;

    GameState gameState;

    Scoreboard *scoreboard;
};

