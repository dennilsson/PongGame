#include <iostream> // required for sqrt()

#include "Vector2.h"



int Vector2::GetLength() const
{
    // Uses pythagoras theorem to the calculate the length of the vector
    return sqrt(x*x + y*y);
}


void Vector2::SetX(int n)
{
    x = n;
}


void Vector2::SetY(int n)
{
    y = n;
}


int Vector2::GetX() const
{
    return x;
}


int Vector2::GetY() const
{
    return y;
}


Vector2 Vector2::operator+(const Vector2 &vec2) const
{
    return Vector2(x + vec2.x, y + vec2.y);
}


Vector2 Vector2::operator-(const Vector2 &vec2) const
{
    return Vector2(x - vec2.GetX(), y - vec2.GetY());
}


Vector2 Vector2::operator*(float s) const
{
    return Vector2(x * s, y * s);
}


Vector2 Vector2::operator/(float s) const
{
    return Vector2(x / s, y / s);
}
