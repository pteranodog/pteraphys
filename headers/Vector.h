class Vector
{
    private:
        float x;
        float y;
        float z;
    public:
        Vector();
        Vector(float newX, float newY);
        Vector(float newX, float newY, float newZ);
        float X();
        float Y();
        float Z();
        void setX(float newX);
        void setY(float newY);
        void setZ(float newZ);
        void set(float newX, float newY);
        void set(float newX, float newY, float newZ);
        void add(Vector v);
        void sub(Vector v);
        void mul(float s);
        void div(float s);
        float mag();
        float magSq();
        void normalize();
        float dot(Vector v);
        Vector cross(Vector v);
        float angle(Vector v);
        float angle();
        float angleXY();
        float angleXZ();
        float angleYZ();
        void rotate2D(float angle);
        Vector lerp(float t);
        void limit(float max);
        void setMag(float mag);
        void setMagSq(float magSq);
        Vector copy();
        Vector copyNormalized();
        Vector copyLimited(float max);
        Vector copyRotated2D(float angle);

};