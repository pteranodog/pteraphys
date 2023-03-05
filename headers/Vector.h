#pragma once
class Vector
{
    private:
        float x;
        float y;
    public:
        Vector();
        Vector(float newX, float newY);
        float X();
        float Y();
        void setX(float newX);
        void setY(float newY);
        void set(float newX, float newY);
        void add(Vector v);
        void sub(Vector v);
        void mult(float s);
        void div(float s);
        float mag();
        float magSq();
        void normalize();
        float dot(Vector v);
        float angle(Vector v);
        float angle();
        void rotate(float angle);
        Vector lerp(float t);
        void limit(float max);
        void setMag(float mag);
        void setMagSq(float magSq);
        Vector copy();
        Vector copyNormalized();
        Vector copyLimited(float max);
        Vector copyRotated(float angle);

};