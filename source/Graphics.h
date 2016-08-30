#pragma once

#include <SDL.h>
#include <iostream>


class Graphics
{
public:
    void Render(SDL_Rect *screen_object);
    
    bool Init(SDL_Window *window);
    void PresentScreen();
    void ClearScreen();

private:
    SDL_Renderer *renderer;
};
