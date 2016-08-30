#include "Ball.h"


//-----------------------------------------------------------------------------
// The default constructor initializes the screen object and the volocity
//-----------------------------------------------------------------------------

Ball::Ball()
{
    position.SetX(SCREEN_WIDTH / 2);
    position.SetY(GetRandomPosition(0, SCREEN_HEIGHT));

    // Sets the default value of the object
    screenObject = { 100, 100, BALL_WIDTH, BALL_HEIGHT };

    // Sets the default volocity speed of the ball
    velocity.SetX(BALL_SPEED);
    velocity.SetY(BALL_SPEED);
}

//-----------------------------------------------------------------------------
// Check if the ball object is colliding with another game object
//-----------------------------------------------------------------------------

bool Ball::CheckCollision(GameObject &object)
{
    // Test for bounding box collision
    if (
        object.GetX() <= (screenObject.x + screenObject.w) &&
        (object.GetX() + object.GetWidth()) >= screenObject.x &&
        object.GetY() < (screenObject.y + screenObject.h) &&
        (object.GetY() + object.GetHeight()) > screenObject.y)
    {

        if (velocity.GetX() > 0)
        {
            velocity.SetX(-BALL_SPEED);
        }
        else if (velocity.GetX() < 0)
        {
            velocity.SetX(BALL_SPEED);
        }

        std::cout << "pos " << position.GetX() << "," << position.GetY() << std::endl;

        return true;
    }

    return false;
}

//-----------------------------------------------------------------------------
// Updates the ball each frame
//-----------------------------------------------------------------------------

void Ball::Update()
{
    // Check if the ball has a collision on the bottom or upper wall.
    if (position.GetY() >= SCREEN_HEIGHT - BALL_HEIGHT)
    {
        velocity.SetY(-BALL_SPEED);
    }
    else if (position.GetY() <= 0)
    {
        velocity.SetY(BALL_SPEED);
    }

    position = position + velocity;

    screenObject.x = position.GetX();
    screenObject.y = position.GetY();
}

//-----------------------------------------------------------------------------
// Render the object to the backbuffer
//-----------------------------------------------------------------------------

void Ball::Draw(Graphics *graphics)
{
	graphics->Render(&screenObject);
}

//-----------------------------------------------------------------------------
// Resets the position of the ball
//-----------------------------------------------------------------------------

void Ball::ResetPosition()
{
    position.SetX(SCREEN_WIDTH / 2);
    position.SetY(GetRandomPosition(0, SCREEN_HEIGHT));
}

