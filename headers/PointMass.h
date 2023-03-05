#include "Vector.h"

#pragma once
class PointMass
{
    private:
        Vector position;
        Vector velocity;
        float mass;
        Vector forces;
    public:
        PointMass();
        PointMass(Vector newPosition, Vector newVelocity, float newMass);
        Vector getPosition();
        Vector getVelocity();
        float getMass();
        void setPosition(Vector newPosition);
        void setVelocity(Vector newVelocity);
        void setMass(float newMass);
        void addForce(Vector force);
        void update(float dt);
};