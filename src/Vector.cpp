#include "Vector.h"
#include <math.h>

Vector::Vector()
{
    x = 1;
    y = 0;
}

Vector::Vector(double newX, double newY)
{
    x = newX;
    y = newY;
}

double Vector::X()
{
    return x;
}

double Vector::Y()
{
    return y;
}

void Vector::setX(double newX)
{
    x = newX;
}

void Vector::setY(double newY)
{
    y = newY;
}

void Vector::set(double newX, double newY)
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

void Vector::mult(double s)
{
    x *= s;
    y *= s;
}

void Vector::div(double s)
{
    if (s == 0)
    {
        throw "Division by zero";
        return;
    }
    x /= s;
    y /= s;
}

double Vector::mag()
{
    return sqrt(x * x + y * y);
}

double Vector::magSq()
{
    return x * x + y * y;
}

void Vector::normalize()
{
    double m = mag();
    if (m == 0)
    {
        throw "Cannot normalize a zero vector";
        return;
    }
    x /= m;
    y /= m;
}

Vector Vector::normal()
{
    return Vector(-y, x);
}

double Vector::dot(Vector v)
{
    return x * v.X() + y * v.Y();
}

double Vector::angle(Vector v)
{
    return acos(dot(v) / (mag() * v.mag()));
}

double Vector::angle()
{
    return atan2(y, x);
}

void Vector::rotate(double angle)
{
    double m = mag();
    double a = atan2(y, x);
    x = m * cos(a + angle);
    y = m * sin(a + angle);
}

Vector Vector::lerp(double t)
{
    return Vector(x * t, y * t);
}

void Vector::limit(double max)
{
    if (magSq() > max * max)
    {
        normalize();
        mult(max);
    }
}

void Vector::setMag(double mag)
{
    normalize();
    mult(mag);
}

void Vector::setMagSq(double magSq)
{
    setMag(sqrt(magSq));
}

Vector Vector::copy()
{
    return Vector(x, y);
}

Vector Vector::operator + (Vector v)
{
    return Vector(x + v.X(), y + v.Y());
}

Vector Vector::operator - (Vector v)
{
    return Vector(x - v.X(), y - v.Y());
}

Vector Vector::operator * (double s)
{
    return Vector(x * s, y * s);
}

Vector Vector::operator / (double s)
{
    if (s == 0)
    {
        throw "Division by zero";
        return Vector();
    }
    return Vector(x / s, y / s);
}

void Vector::operator += (Vector v)
{
    x += v.X();
    y += v.Y();
}

void Vector::operator -= (Vector v)
{
    x -= v.X();
    y -= v.Y();
}

void Vector::operator *= (double s)
{
    x *= s;
    y *= s;
}

void Vector::operator /= (double s)
{
    if (s == 0)
    {
        throw "Division by zero";
    }
    x /= s;
    y /= s;
}

bool Vector::operator == (Vector v)
{
    return x == v.X() && y == v.Y();
}

bool Vector::operator != (Vector v)
{
    return x != v.X() || y != v.Y();
}

bool Vector::operator < (Vector v)
{
    return magSq() < v.magSq();
}

bool Vector::operator <= (Vector v)
{
    return magSq() <= v.magSq();
}

bool Vector::operator > (Vector v)
{
    return magSq() > v.magSq();
}

bool Vector::operator >= (Vector v)
{
    return magSq() >= v.magSq();
}

void Vector::operator = (Vector v)
{
    x = v.X();
    y = v.Y();
}


