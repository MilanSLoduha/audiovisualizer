#include "window.hpp"
#include "Globals.hpp"

window::window() {
}

void window::windowRun()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "Krilo - vizual");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

}



