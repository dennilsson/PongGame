#include "Graphics.h"



//-----------------------------------------------------------------------------
// Initialize the render
//-----------------------------------------------------------------------------

bool Graphics::Init(SDL_Window *window)
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == nullptr)
    {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}


//-----------------------------------------------------------------------------
// This function will render the SDL_Rect object to the screen
//-----------------------------------------------------------------------------

void Graphics::Render(SDL_Rect *screen_object)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderDrawRect(renderer, screen_object);

    SDL_RenderFillRect(renderer, screen_object);
}


//-----------------------------------------------------------------------------
// This function is responsible for flipping the backbuffer to the frontbuffer
//-----------------------------------------------------------------------------

void Graphics::PresentScreen()
{
    SDL_RenderPresent(renderer);
}


//-----------------------------------------------------------------------------
// Clears the screen to a solid color
//-----------------------------------------------------------------------------

void Graphics::ClearScreen()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}
