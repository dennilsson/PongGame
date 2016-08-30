#pragma once


class Vector2
{
public:
    Vector2() {}
    Vector2(int x, int y) : x(x), y(y) {}

    int GetLength() const;

    void SetX(int x);
    void SetY(int y);

    int GetX() const;
    int GetY() const;

    Vector2 operator+(const Vector2 &vec2) const;
    Vector2 operator-(const Vector2 &vec2) const;
    Vector2 operator*(float s) const;
    Vector2 operator/(float s) const;

private:
    int x = 0;
    int y = 0;
};
