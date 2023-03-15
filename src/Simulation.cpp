#include "Simulation.h"
#include "PointMass.h"
#include "LinkConstraint.h"
#include "CircleAreaConstraint.h"
#include <SFML/Graphics.hpp>

Simulation::Simulation()
{
    Vector gravity = Vector(0, 0);
    FPS = 60;
    subSteps = 1;
    dt = 1.0 / FPS / subSteps;
    constraintIterations = 1;
    collisionIterations = 1;
    backgroundColor = sf::Color::Black;
    background = sf::RectangleShape(sf::Vector2f(1920, 1080));
    background.setFillColor(backgroundColor);
}

Simulation::Simulation(int simFPS, int simSubSteps, int simConstraintIterations, int simCollisionIterations, sf::Color simBackgroundColor)
{
    gravity = Vector(0, 0);
    FPS = simFPS;
    subSteps = simSubSteps;
    dt = 1.0 / FPS / subSteps;
    constraintIterations = simConstraintIterations;
    collisionIterations = simCollisionIterations;
    backgroundColor = simBackgroundColor;
    background = sf::RectangleShape(sf::Vector2f(1920, 1080));
    background.setFillColor(backgroundColor);
}

Simulation::~Simulation()
{
    for (int i = 0; i < pointMasses.size(); i++)
    {
        delete pointMasses[i];
    }
    for (int i = 0; i < linkConstraints.size(); i++)
    {
        delete linkConstraints[i];
    }
    for (int i = 0; i < circleAreaConstraints.size(); i++)
    {
        delete circleAreaConstraints[i];
    }
}

void Simulation::setGravity(Vector newGravity)
{
    gravity = newGravity;
}

void Simulation::addPointMass(PointMass *newPointMass)
{
    pointMasses.push_back(newPointMass);
}

void Simulation::addLinkConstraint(LinkConstraint *newLinkConstraint)
{
    linkConstraints.push_back(newLinkConstraint);
}

void Simulation::addCircleAreaConstraint(CircleAreaConstraint *newCircleAreaConstraint)
{
    circleAreaConstraints.push_back(newCircleAreaConstraint);
}

void Simulation::update()
{
    for (int i = 0; i < subSteps; i++)
    {
        applyForcesAndMove();
        for (int j = 0; j < collisionIterations; j++)
        {
            checkCollisions();
        }
        for (int j = 0; j < constraintIterations; j++)
        {
            applyConstraints();
        }
    }
}

void Simulation::draw(sf::RenderWindow &window)
{
    window.draw(background);
    for (int i = 0; i < circleAreaConstraints.size(); i++)
    {
        circleAreaConstraints[i]->draw(window);
    }
    for (int i = 0; i < linkConstraints.size(); i++)
    {
        linkConstraints[i]->draw(window);
    }
    for (int i = 0; i < pointMasses.size(); i++)
    {
        pointMasses[i]->draw(window);
    }    
}

void Simulation::applyConstraints()
{
    for (int i = 0; i < linkConstraints.size(); i++)
    {
        linkConstraints[i]->applyConstraint();
    }
    for (int i = 0; i < circleAreaConstraints.size(); i++)
    {
        for (int j = 0; j < pointMasses.size(); j++)
        {
            circleAreaConstraints[i]->applyConstraint(*pointMasses[j]);
        }
    }
}

void Simulation::applyForcesAndMove()
{
    for (int i = 0; i < pointMasses.size(); i++)
    {
        pointMasses[i]->addForce(gravity * pointMasses[i]->getMass());
        pointMasses[i]->applyForcesAndMove(dt);
    }
}

void Simulation::checkCollisions()
{
    for (int i = 0; i < pointMasses.size(); i++)
    {
        for (int j = i + 1; j < pointMasses.size(); j++)
        {
            pointMasses[i]->checkCollision(pointMasses[j]);
        }
    }
    for (int i = 0; i < linkConstraints.size(); i++)
    {
        for (int j = 0; j < pointMasses.size(); j++)
        {
            linkConstraints[i]->checkCollision(pointMasses[j]);
        }
    }
}

std::vector <PointMass*> Simulation::getPointMasses()
{
    return pointMasses;
}

std::vector <LinkConstraint*> Simulation::getLinkConstraints()
{
    return linkConstraints;
}

std::vector <CircleAreaConstraint*> Simulation::getCircleAreaConstraints()
{
    return circleAreaConstraints;
}