#include "PointMass.h"
#include "Vector.h"

PointMass::PointMass()
{
    position = Vector(0, 0);
    velocity = Vector(0, 0);
    mass = 1;
    forces = Vector(0, 0);
}

PointMass::PointMass(Vector newPosition, Vector newVelocity, float newMass)
{
    position = newPosition;
    velocity = newVelocity;
    mass = newMass;
    forces = Vector(0, 0);
}

Vector PointMass::getPosition()
{
    return position;
}

Vector PointMass::getVelocity()
{
    return velocity;
}

float PointMass::getMass()
{
    return mass;
}

void PointMass::setPosition(Vector newPosition)
{
    position = newPosition;
}

void PointMass::setVelocity(Vector newVelocity)
{
    velocity = newVelocity;
}

void PointMass::setMass(float newMass)
{
    mass = newMass;
}

void PointMass::addForce(Vector force)
{
    forces.add(force);
}

void PointMass::update(float dt)
{
    // More complex than normal because Verlet integration is used
    // Position is calculated as (previous position + velocity * dt + 0.5 * acceleration * dt^2)
    // Velocity is calculated as (previous velocity + acceleration * dt)

    // Acceleration is total force divided by mass
    Vector acceleration = forces.copy();
    acceleration.div(mass);

    // To achieve this, we first make a copy of velocity and multiply it by dt
    // We then skip to updating velocity
    Vector deltaPosition = velocity.copy();
    deltaPosition.mult(dt);

    // Acceleration is then multiplied by dt and added to velocity
    acceleration.mult(dt);
    velocity.add(acceleration);

    // Acceleration has already been multiplied by dt once
    // Now, to get 0.5 * acceleration * dt^2, we multiply it by 0.5 * dt
    // Then add it to deltaPosition
    acceleration.mult(0.5 * dt);
    deltaPosition.add(acceleration);

    // Finally, add deltaPosition to position and reset forces
    position.add(deltaPosition);
    forces.set(0, 0);
}