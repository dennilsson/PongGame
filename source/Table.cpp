#include "Table.h"



Table::Table()
{
    int x = SCREEN_WIDTH / 2;
    int y = 0;

    while (y < SCREEN_HEIGHT)
    {
        SDL_Rect rect = { x, y, LINE_WIDTH, LINE_HEIGHT };
        screenObjects.push_back(rect);

        y += LINE_HEIGHT + LINE_SPACE;
    }
}


void Table::Draw(Graphics *graphics)
{
    for (auto &i : screenObjects)
    {
        graphics->Render(&i);
    }
}