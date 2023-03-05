#include <SFML/Graphics.hpp>
#include "Vector.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "PteraPhys");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    Vector pos(0, 0);
    Vector vel(1, 1);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        shape.setPosition(pos.X(), pos.Y());
        pos.add(vel);
        if (pos.X() > 1080 || pos.X() < 0)
        {
            vel.setX(-vel.X());
        }
        if (pos.Y() > 520 || pos.Y() < 0)
        {
            vel.setY(-vel.Y());
        }
        window.draw(shape);
        window.display();
    }

    return 0;
}