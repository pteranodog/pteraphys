#include "PointMass.h"
#include "Vector.h"
#include <SFML/Graphics.hpp>

#pragma once
class CircleAreaConstraint
{
    private:
        double radius;
        double radiusSq;
        Vector center;

        sf::CircleShape shape;
        sf::Color fillColor;
    public:
        CircleAreaConstraint();
        CircleAreaConstraint(double newRadius, Vector newCenter, sf::Color color);
        void applyConstraint(PointMass &massToConstrain);
        void draw(sf::RenderWindow &window);
};