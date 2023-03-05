#include "Vector.h"
#include <math.h>

Vector::Vector()
{
    x = 0;
    y = 0;
    z = 0;
}

Vector::Vector(float newX, float newY)
{
    x = newX;
    y = newY;
    z = 0;
}

Vector::Vector(float newX, float newY, float newZ)
{
    x = newX;
    y = newY;
    z = newZ;
}

float Vector::X()
{
    return x;
}

float Vector::Y()
{
    return y;
}

float Vector::Z()
{
    return z;
}

void Vector::setX(float newX)
{
    x = newX;
}

void Vector::setY(float newY)
{
    y = newY;
}

void Vector::setZ(float newZ)
{
    z = newZ;
}

void Vector::set(float newX, float newY)
{
    x = newX;
    y = newY;
}

void Vector::set(float newX, float newY, float newZ)
{
    x = newX;
    y = newY;
    z = newZ;
}

void Vector::add(Vector v)
{
    x += v.X();
    y += v.Y();
    z += v.Z();
}

void Vector::sub(Vector v)
{
    x -= v.X();
    y -= v.Y();
    z -= v.Z();
}

void Vector::mult(float s)
{
    x *= s;
    y *= s;
    z *= s;
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
    z /= s;
}

float Vector::mag()
{
    return sqrt(x * x + y * y + z * z);
}

float Vector::magSq()
{
    return x * x + y * y + z * z;
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
    z /= m;
}

float Vector::dot(Vector v)
{
    return x * v.X() + y * v.Y() + z * v.Z();
}

Vector Vector::cross(Vector v)
{
    return Vector(y * v.Z() - z * v.Y(), z * v.X() - x * v.Z(), x * v.Y() - y * v.X());
}

float Vector::angle(Vector v)
{
    return acos(dot(v) / (mag() * v.mag()));
}

float Vector::angle()
{
    return atan2(y, x);
}

float Vector::angleXY()
{
    return atan2(y, x);
}

float Vector::angleXZ()
{
    return atan2(z, x);
}

float Vector::angleYZ()
{
    return atan2(z, y);
}

void Vector::rotate2D(float angle)
{
    if (z != 0)
    {
        throw "Cannot 2D rotate a 3D vector";
        return;
    }
    float m = mag();
    float a = atan2(y, x);
    x = m * cos(a + angle);
    y = m * sin(a + angle);
}

Vector Vector::lerp(float t)
{
    return Vector(x * t, y * t, z * t);
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
    return Vector(x, y, z);
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

Vector Vector::copyRotated2D(float angle)
{
    Vector v = copy();
    v.rotate2D(angle);
    return v;
}