#include "Paddle.h"


Paddle::Paddle(int x, int y)
{
    // Set the initial position of the paddle
    position.SetX(x);
    position.SetY(y);
    
    // Set the initial speed
    velocity.SetX(0);
    velocity.SetY(0);

    screenObject = { x, y, PADDLE_WIDTH, PADDLE_HEIGHT };
}


//-----------------------------------------------------------------------------
// The Update() method gets called every frame
//-----------------------------------------------------------------------------

void Paddle::Update()
{
    // Checks to see if the object has collided with the upper or lower wall
    if (position.GetY() + PADDLE_HEIGHT >= SCREEN_HEIGHT)
    {
        MoveUp();
    }
    else if (position.GetY() <= 0)
    {
        MoveDown();
    }

    position = position + velocity;

    screenObject.y = position.GetY();
}


//-----------------------------------------------------------------------------
// The draw() method gets called every frame
//-----------------------------------------------------------------------------

void Paddle::Draw(Graphics *graphics)
{
    graphics->Render(&screenObject);
}


void Paddle::MoveDown()
{
    velocity.SetY(PADDLE_SPEED);
}


void Paddle::MoveUp()
{
    velocity.SetY(-PADDLE_SPEED);
}


void Paddle::StopMoving()
{
    velocity.SetY(0);
}


void Paddle::AddScore()
{
    score++;
}