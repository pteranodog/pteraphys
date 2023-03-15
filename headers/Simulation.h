#include <vector>
#include "PointMass.h"
#include "LinkConstraint.h"
#include "CircleAreaConstraint.h"
#include <SFML/Graphics.hpp>

#pragma once
class Simulation
{
    private:
        std::vector<PointMass*> pointMasses;
        std::vector<LinkConstraint*> linkConstraints;
        std::vector<CircleAreaConstraint*> circleAreaConstraints;
        Vector gravity;

        int FPS;
        int subSteps;
        int constraintIterations;
        int collisionIterations;
        double dt;

        sf::Color backgroundColor;
        sf::RectangleShape background;

        void applyConstraints();
        void applyForcesAndMove();
        void checkCollisions();

    public:
        Simulation();
        Simulation(int simFPS, int simSubSteps, int simConstraintIterations, int simCollisionIterations, sf::Color simBackgroundColor);
        ~Simulation();
        void setGravity(Vector newGravity);
        void addPointMass(PointMass *newPointMass);
        void addLinkConstraint(LinkConstraint *newLinkConstraint);
        void addCircleAreaConstraint(CircleAreaConstraint *newCircleAreaConstraint);
        std::vector <PointMass*> getPointMasses();
        std::vector <LinkConstraint*> getLinkConstraints();
        std::vector <CircleAreaConstraint*> getCircleAreaConstraints();
        void update();
        void draw(sf::RenderWindow &window);
};