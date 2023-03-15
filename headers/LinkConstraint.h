#include "PointMass.h"
#include "Vector.h"
#include <SFML/Graphics.hpp>

#pragma once
class LinkConstraint
{
    private:
        double length;
        double halfThickness;
        bool collidable;
        PointMass *mass1;
        PointMass *mass2;
        sf::Color color;
        sf::RectangleShape shape;

        Vector nearestToPoint(Vector point);
        Vector nearestToPoint(Vector point, double &t);
    public:
        LinkConstraint();
        LinkConstraint(PointMass *newMass1, PointMass *newMass2, double newHalfThickness, bool isCollidable, sf::Color newColor);
        void applyConstraint();
        void draw(sf::RenderWindow &window);
        void checkCollision(PointMass *otherMass);
};