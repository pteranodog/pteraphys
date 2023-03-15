#include "PointMass.h"
#include "Vector.h"
#include <SFML/Graphics.hpp>
#include "CircleAreaConstraint.h"

CircleAreaConstraint::CircleAreaConstraint()
{
    radius = 100;
    radiusSq = radius * radius;
    center = Vector(0, 0);
    fillColor = sf::Color::White;
    shape = sf::CircleShape(radius, 128);
    shape.setFillColor(fillColor);
    shape.setPosition(center.X() - radius, center.Y() - radius);
}

CircleAreaConstraint::CircleAreaConstraint(double newRadius, Vector newCenter, sf::Color color)
{
    radius = newRadius;
    radiusSq = radius * radius;
    center = newCenter;
    fillColor = color;
    shape = sf::CircleShape(radius, 128);
    shape.setFillColor(fillColor);
    shape.setPosition(center.X() - radius, center.Y() - radius);
}

void CircleAreaConstraint::applyConstraint(PointMass &massToConstrain)
{
    Vector massPosition = massToConstrain.getPosition();
    double massRadius = massToConstrain.getRadius();
    Vector direction = massPosition - center;
    if (direction.magSq() <= (radius - massRadius) * (radius - massRadius))
    {
        return;
    }
    direction.normalize();
    Vector radiusSubtract = direction * massRadius;
    Vector newPosition = center + direction * radius - radiusSubtract;
    massToConstrain.setPosition(newPosition);
}

void CircleAreaConstraint::draw(sf::RenderWindow &window)
{
    window.draw(shape);
}