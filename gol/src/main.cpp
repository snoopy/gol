#include "model.h"
#include "view.h"
#include "controller.h"

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

int main() {
    constexpr int width = 1440;
    constexpr int height = 900;

    sf::RenderWindow window(sf::VideoMode(width, height), "0",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    GameOfLife::Controller controller{width, height, window};

    constexpr float update_delay = .5;
    sf::Clock clock;
    clock.restart();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    controller.on_keypress(event);
                    break;

                default:
                    break;
            }
        }

        window.clear();

        if (clock.getElapsedTime().asSeconds() >= update_delay) {
            controller.update_model();
            clock.restart();
        }

        controller.display_view();

        window.display();
    }
}
