#include <SFML/Graphics.hpp>
#include "Simulation.h"
#include "Vector.h"
#include "PointMass.h"
#include "CircleAreaConstraint.h"
#include "LinkConstraint.h"
#include <iostream>

void handleEvent(sf::Event event, sf::RenderWindow &window, Simulation &sim, float &windowScale, Vector &windowOffset);
void handleMouseButtonPressed(sf::Event event, sf::RenderWindow &window, Simulation &sim);
void handleMouseWheelScrolled(sf::Event event, sf::RenderWindow &window, float &windowScale, Vector &windowOffset);
void handleKeyPressed(sf::Event event, sf::RenderWindow &window, float &windowScale, Vector &windowOffset);

int main()
{
    float windowScale = 1.0;
    Vector windowOffset = Vector(0, 0);
    int FPS = 60;
    sf::RenderWindow window(sf::VideoMode(800, 800), "PteraPhys");
    window.setFramerateLimit(FPS);
    
    Simulation sim(FPS, 8, 2, 2, sf::Color::Black);
    sim.setGravity(Vector(0, 400));
    sim.addCircleAreaConstraint(new CircleAreaConstraint(400, Vector(400, 400), sf::Color::White));    

    int counter = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            handleEvent(event, window, sim, windowScale, windowOffset);
        }
        counter++;
        if (counter % 25 == 0 && counter < 3750)
        {
            sim.addPointMass(new PointMass(Vector(200, 200), 1.5, 15, sf::Color(150, 0, 150)));
        }
        sim.update();
        window.clear();
        sim.draw(window);
        window.display();
    }
    return 0;
}

void handleEvent(sf::Event event, sf::RenderWindow &window, Simulation &sim, float &windowScale, Vector &windowOffset)
{
    if (event.type == sf::Event::Closed)
    {
        window.close();
    }
    if (event.type == sf::Event::Resized)
    {
        window.setView(sf::View(sf::FloatRect(windowOffset.X(), windowOffset.Y(), event.size.width * windowScale, event.size.height * windowScale)));
    }
    if (event.type == sf::Event::MouseButtonPressed)
    {
        handleMouseButtonPressed(event, window, sim);
    }
    if (event.type == sf::Event::MouseWheelScrolled)
    {
        handleMouseWheelScrolled(event, window, windowScale, windowOffset);
    }
    if (event.type == sf::Event::KeyPressed)
    {
        handleKeyPressed(event, window, windowScale, windowOffset);
    }
}

void handleMouseButtonPressed(sf::Event event, sf::RenderWindow &window, Simulation &sim)
{
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f location = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
        sim.addPointMass(new PointMass(Vector(location.x, location.y), 1, 10, sf::Color::Red));
    }
    if (event.mouseButton.button == sf::Mouse::Right)
    {
        sf::Vector2f location = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
        sim.addPointMass(new PointMass(Vector(location.x, location.y), 4, 20, sf::Color::Blue));
    }
}

void handleMouseWheelScrolled(sf::Event event, sf::RenderWindow &window, float &windowScale, Vector &windowOffset)
{
    if (event.mouseWheelScroll.delta < 0)
    {
        windowOffset -= Vector(event.mouseWheelScroll.x, event.mouseWheelScroll.y) * (0.1 * windowScale);
        windowScale *= 1.1;
    }
    else
    {
        windowOffset += Vector(event.mouseWheelScroll.x, event.mouseWheelScroll.y) * (0.1 * windowScale);
        windowScale *= 0.9;
    }
    window.setView(sf::View(sf::FloatRect(windowOffset.X(), windowOffset.Y(), window.getSize().x * windowScale, window.getSize().y * windowScale)));
}

void handleKeyPressed(sf::Event event, sf::RenderWindow &window, float &windowScale, Vector &windowOffset)
{
    if (event.key.code == sf::Keyboard::W)
    {
        windowOffset += Vector(0, -50) * windowScale;
    }
    if (event.key.code == sf::Keyboard::A)
    {
        windowOffset += Vector(-50, 0) * windowScale;
    }
    if (event.key.code == sf::Keyboard::S)
    {
        windowOffset += Vector(0, 50) * windowScale;
    }
    if (event.key.code == sf::Keyboard::D)
    {
        windowOffset += Vector(50, 0) * windowScale;
    }
    if (event.key.code == sf::Keyboard::R)
    {
        windowOffset = Vector(0, 0);
        windowScale = 1.0;
    }
    window.setView(sf::View(sf::FloatRect(windowOffset.X(), windowOffset.Y(), window.getSize().x * windowScale, window.getSize().y * windowScale)));
}