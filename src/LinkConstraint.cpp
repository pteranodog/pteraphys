#include "PointMass.h"
#include "Vector.h"
#include <SFML/Graphics.hpp>
#include "LinkConstraint.h"

LinkConstraint::LinkConstraint()
{
    length = 100;
    halfThickness = 5;
    mass1 = nullptr;
    mass2 = nullptr;
    color = sf::Color::White;
    shape = sf::RectangleShape(sf::Vector2f(length, halfThickness * 2));
    shape.setFillColor(color);
    shape.setOrigin(0, halfThickness);
}

LinkConstraint::LinkConstraint(PointMass *newMass1, PointMass *newMass2, double newHalfThickness, bool isCollidable, sf::Color newColor)
{;
    halfThickness = newHalfThickness;
    collidable = isCollidable;
    mass1 = newMass1;
    mass2 = newMass2;
    color = newColor;
    length = (mass2->getPosition() - mass1->getPosition()).mag();
    shape = sf::RectangleShape(sf::Vector2f(length, halfThickness * 2));
    shape.setFillColor(color);
    shape.setOrigin(0, halfThickness);
}

void LinkConstraint::applyConstraint()
{
    Vector mass1Position = mass1->getPosition();
    Vector mass2Position = mass2->getPosition();
    Vector direction = mass2Position - mass1Position;
    double currentLength = direction.mag();
    direction.normalize();
    double mass1Ratio = mass1->getMass() / (mass1->getMass() + mass2->getMass());
    double mass2Ratio = mass2->getMass() / (mass1->getMass() + mass2->getMass());
    Vector newPosition1 = mass1Position + direction * (currentLength - length) * mass1Ratio;
    Vector newPosition2 = mass2Position - direction * (currentLength - length) * mass2Ratio;
    mass1->setPosition(newPosition1);
    mass2->setPosition(newPosition2);
}

void LinkConstraint::draw(sf::RenderWindow &window)
{
    Vector mass1Position = mass1->getPosition();
    Vector mass2Position = mass2->getPosition();
    Vector direction = mass2Position - mass1Position;
    double currentLength = direction.mag();
    direction.normalize();
    double angle = direction.angle() * 180 / 3.14159265358979323846;
    shape.setPosition(mass1Position.X(), mass1Position.Y());
    shape.setRotation(angle);
    window.draw(shape);
}

Vector LinkConstraint::nearestToPoint(Vector point)
{
    double t;
    return nearestToPoint(point, t);
}

Vector LinkConstraint::nearestToPoint(Vector point, double &t)
{
    double actualLengthSq = (mass2->getPosition() - mass1->getPosition()).magSq();
    if (actualLengthSq == 0)
    {
        return mass1->getPosition();
    }
    Vector mass1Position = mass1->getPosition();
    Vector mass2Position = mass2->getPosition();
    t = ((point.X() - mass1Position.X()) * (mass2Position.X() - mass1Position.X()) + (point.Y() - mass1Position.Y()) * (mass2Position.Y() - mass1Position.Y())) / actualLengthSq;
    if (t <= 0)
    {
        return mass1Position;
    }
    else if (t >= 1)
    {
        return mass2Position;
    }
    else
    {
        return mass1Position + (mass2Position - mass1Position) * t;
    }
}

void LinkConstraint::checkCollision(PointMass *otherMass)
{   
    if (!collidable || otherMass == mass1 || otherMass == mass2)
    {
        return;
    }
    Vector otherPosition = otherMass->getPosition();
    double targetDistance = halfThickness + otherMass->getRadius();
    double t;
    Vector nearestPoint = nearestToPoint(otherPosition, t);
    Vector direction = otherPosition - nearestPoint;
    double distance = direction.mag();
    if (distance > targetDistance || t < 0 || t > 1)
    {
        return;
    }
    if (distance == 0)
    {
        direction = (mass2->getPosition() - mass1->getPosition()).normal();
    }
    direction.normalize();
    double totalDistanceToMove = (distance - targetDistance) * otherMass->getMass() / (mass1->getMass() + mass2->getMass() + otherMass->getMass());
    Vector newPosition1 = mass1->getPosition() + direction * t * totalDistanceToMove;
    Vector newPosition2 = mass2->getPosition() + direction * (1 - t) * totalDistanceToMove;
    mass1->setPosition(newPosition1);
    mass2->setPosition(newPosition2);
    Vector newNearestPoint = nearestToPoint(otherPosition);
    Vector newDirection = otherPosition - newNearestPoint;
    newDirection.normalize();
    otherMass->setPosition(newNearestPoint + (newDirection * targetDistance));
}