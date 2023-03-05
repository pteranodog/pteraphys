#include <SFML/Graphics.hpp>
#include "Vector.h"
#include "PointMass.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "PteraPhys");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    PointMass mass(Vector(0, 0), Vector(1, 1), 1);
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        mass.update(clock.restart().asSeconds());
        if (mass.getPosition().X() > 1.080 || mass.getPosition().X() < 0)
        {
            mass.setVelocity(Vector(-mass.getVelocity().X(), mass.getVelocity().Y()));
            mass.setPosition(Vector(mass.getPosition().X() < 0 ? 0 : 1.080, mass.getPosition().Y()));
        }
        if (mass.getPosition().Y() > 0.520 || mass.getPosition().Y() < 0)
        {
            mass.setVelocity(Vector(mass.getVelocity().X(), -mass.getVelocity().Y()));
            mass.setPosition(Vector(mass.getPosition().X(), mass.getPosition().Y() < 0 ? 0 : 0.520));
        }
        shape.setPosition(mass.getPosition().X()*1000, mass.getPosition().Y()*1000);
        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}