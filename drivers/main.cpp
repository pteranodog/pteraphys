#include <SFML/Graphics.hpp>
#include "Simulation.h"
#include "Vector.h"
#include "PointMass.h"
#include "CircleAreaConstraint.h"
#include "LinkConstraint.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "PteraPhys");
    window.setFramerateLimit(60);
    int FPS = 60;
    Simulation sim(FPS, 8, 2, 2, sf::Color::Black);
    sim.setGravity(Vector(0, 400));
    sim.addCircleAreaConstraint(new CircleAreaConstraint(400, Vector(400, 400), sf::Color::White));    

    int counter = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::Resized)
            {
                window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sim.addPointMass(new PointMass(Vector(event.mouseButton.x, event.mouseButton.y), 1, 10, sf::Color::Red));
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    sim.addPointMass(new PointMass(Vector(event.mouseButton.x, event.mouseButton.y), 4, 20, sf::Color::Blue));
                }
            }
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