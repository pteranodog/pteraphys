#pragma once
class Vector
{
    private:
        double x;
        double y;
    public:
        Vector();
        Vector(double newX, double newY);
        double X();
        double Y();
        void setX(double newX);
        void setY(double newY);
        void set(double newX, double newY);
        void add(Vector v);
        void sub(Vector v);
        void mult(double s);
        void div(double s);
        double mag();
        double magSq();
        void normalize();
        double dot(Vector v);
        double angle(Vector v);
        double angle();
        void rotate(double angle);
        Vector normal();
        Vector lerp(double t);
        void limit(double max);
        void setMag(double mag);
        void setMagSq(double magSq);
        Vector copy();
        Vector operator + (Vector v);
        Vector operator - (Vector v);
        Vector operator * (double s);
        Vector operator / (double s);
        void operator += (Vector v);
        void operator -= (Vector v);
        void operator *= (double s);
        void operator /= (double s);
        bool operator == (Vector v);
        bool operator != (Vector v);
        bool operator < (Vector v);
        bool operator <= (Vector v);
        bool operator > (Vector v);
        bool operator >= (Vector v);
        void operator = (Vector v);
};