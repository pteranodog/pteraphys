#include "Vector.h"
#include <SFML/Graphics.hpp>

#pragma once
class PointMass
{
    private:
        // Motion and properties
        Vector position;
        Vector previousPosition;
        Vector forces;
        double mass;
        double inverseMass;
        double radius;
        
        // Drawing
        sf::CircleShape shape;
        sf::Color fillColor;

    public:
        PointMass();
        PointMass(Vector newPosition, double newMass, double newRadius, sf::Color color);

        // Getters
        Vector getPosition();
        Vector getPreviousPosition();
        Vector getVelocity(double dt);
        double getMass();
        double getInvMass();
        double getRadius();

        // Setters
        void setPosition(Vector newPosition);
        void setPreviousPosition(Vector newPreviousPosition);
        void setVelocity(Vector newVelocity, double dt);
        void setMass(double newMass);
        void setRadius(double newRadius);

        // Physics
        void addForce(Vector force);
        void applyForcesAndMove(double dt);
        void checkCollision(PointMass *otherMass);
        
        // Drawing
        void draw(sf::RenderWindow &window);
        void setFillColor(sf::Color color);
};