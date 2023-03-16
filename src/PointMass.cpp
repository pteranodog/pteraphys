#include "PointMass.h"
#include "Vector.h"
#include <SFML/Graphics.hpp>

PointMass::PointMass()
{
    position = Vector(0, 0);
    previousPosition = Vector(0, 0);
    mass = 1;
    inverseMass = 1;
    forces = Vector(0, 0);
    radius = 10;
    pinned = false;
    fillColor = sf::Color::Red;
    shape = sf::CircleShape(radius);
    shape.setFillColor(fillColor);
    shape.setPosition(position.X() - radius, position.Y() - radius);
}

PointMass::PointMass(Vector newPosition, double newMass, double newRadius, sf::Color color)
{
    position = newPosition;
    previousPosition = newPosition;
    mass = newMass;
    if (mass == 0)
    {
        inverseMass = 0;
    }
    else
    {
        inverseMass = 1 / mass;
    }
    pinned = false;
    forces = Vector(0, 0);
    radius = newRadius;
    fillColor = color;
    shape = sf::CircleShape(radius);
    shape.setFillColor(fillColor);
    shape.setPosition(position.X() - radius, position.Y() - radius);
}

Vector PointMass::getPosition()
{
    return position;
}

Vector PointMass::getPreviousPosition()
{
    return previousPosition;
}

Vector PointMass::getVelocity(double dt)
{
    return (position - previousPosition) / dt;
}

double PointMass::getMass()
{
    return mass;
}

void PointMass::setPosition(Vector newPosition)
{
    position = newPosition;
}

void PointMass::setPreviousPosition(Vector newPreviousPosition)
{
    previousPosition = newPreviousPosition;
}

void PointMass::setVelocity(Vector newVelocity, double dt)
{
    previousPosition = position - newVelocity * dt;
}

void PointMass::setMass(double newMass)
{
    mass = newMass;
    if (mass == 0)
    {
        inverseMass = 0;
    }
    else
    {
        inverseMass = 1 / mass;
    }
}

void PointMass::addForce(Vector force)
{
    forces.add(force);
}

void PointMass::applyForcesAndMove(double dt)
{
    if (pinned)
    {
        forces = Vector(0, 0);
        return;
    }
    Vector acceleration = forces * inverseMass;
    Vector velocity = position - previousPosition;
    previousPosition = position;
    position = position + velocity + acceleration * dt * dt;
    forces = Vector(0, 0);
}

void PointMass::checkCollision(PointMass *otherMass)
{
    if (otherMass == this)
    {
        return;
    }
    Vector direction = position - otherMass->getPosition();
    double distanceSq = direction.magSq();
    double targetDistance = radius + otherMass->getRadius();
    if (distanceSq < targetDistance * targetDistance)
    {
        double distance = direction.mag();
        if (distance == 0)
        {
            direction = Vector(1, 0);
        }
        double overlap = targetDistance - distance;
        direction.normalize();
        if (pinned && otherMass->isPinned())
        {
            return;
        }
        else if (pinned)
        {
            otherMass->setPosition(otherMass->getPosition() - direction * overlap);
            return;
        }
        else if (otherMass->isPinned())
        {
            position = position + direction * overlap;
            return;
        }
        double totalMassInv = 1.0 / (mass + otherMass->getMass());
        position = position + direction * overlap * otherMass->getMass() * totalMassInv;
        otherMass->setPosition(otherMass->getPosition() - direction * overlap * mass * totalMassInv);
    }
}

void PointMass::draw(sf::RenderWindow &window)
{
    shape.setPosition(position.X() - radius, position.Y() - radius);
    window.draw(shape);
}

void PointMass::setRadius(double newRadius)
{
    radius = newRadius;
    shape.setRadius(radius);
}

double PointMass::getRadius()
{
    return radius;
}

void PointMass::setFillColor(sf::Color color)
{
    fillColor = color;
    shape.setFillColor(fillColor);
}

bool PointMass::isPinned()
{
    return pinned;
}

void PointMass::setPinned(bool newPinned)
{
    pinned = newPinned;
}

void PointMass::pin()
{
    pinned = true;
}

void PointMass::unpin()
{
    pinned = false;
}