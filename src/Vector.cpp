#include "Vector.h"
#include <math.h>

Vector::Vector()
{
    x = 1;
    y = 0;
}

Vector::Vector(float newX, float newY)
{
    x = newX;
    y = newY;
}

float Vector::X()
{
    return x;
}

float Vector::Y()
{
    return y;
}

void Vector::setX(float newX)
{
    x = newX;
}

void Vector::setY(float newY)
{
    y = newY;
}

void Vector::set(float newX, float newY)
{
    x = newX;
    y = newY;
}

void Vector::add(Vector v)
{
    x += v.X();
    y += v.Y();
}

void Vector::sub(Vector v)
{
    x -= v.X();
    y -= v.Y();
}

void Vector::mult(float s)
{
    x *= s;
    y *= s;
}

void Vector::div(float s)
{
    if (s == 0)
    {
        throw "Division by zero";
        return;
    }
    x /= s;
    y /= s;
}

float Vector::mag()
{
    return sqrt(x * x + y * y);
}

float Vector::magSq()
{
    return x * x + y * y;
}

void Vector::normalize()
{
    float m = mag();
    if (m == 0)
    {
        throw "Cannot normalize a zero vector";
        return;
    }
    x /= m;
    y /= m;
}

float Vector::dot(Vector v)
{
    return x * v.X() + y * v.Y();
}

float Vector::angle(Vector v)
{
    return acos(dot(v) / (mag() * v.mag()));
}

float Vector::angle()
{
    return atan2(y, x);
}

void Vector::rotate(float angle)
{
    float m = mag();
    float a = atan2(y, x);
    x = m * cos(a + angle);
    y = m * sin(a + angle);
}

Vector Vector::lerp(float t)
{
    return Vector(x * t, y * t);
}

void Vector::limit(float max)
{
    if (magSq() > max * max)
    {
        normalize();
        mult(max);
    }
}

void Vector::setMag(float mag)
{
    normalize();
    mult(mag);
}

void Vector::setMagSq(float magSq)
{
    setMag(sqrt(magSq));
}

Vector Vector::copy()
{
    return Vector(x, y);
}

Vector Vector::copyNormalized()
{
    Vector v = copy();
    v.normalize();
    return v;
}

Vector Vector::copyLimited(float max)
{
    Vector v = copy();
    v.limit(max);
    return v;
}

Vector Vector::copyRotated(float angle)
{
    Vector v = copy();
    v.rotate(angle);
    return v;
}