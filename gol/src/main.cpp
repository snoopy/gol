#include "gol.h"

#include <SFML/Graphics.hpp>

#include <string>

int main() {
    constexpr int width = 1440;
    constexpr int height = 900;
    Gol gol{width, height};

    sf::RenderWindow window(sf::VideoMode(width, height), "0",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    constexpr float update_delay = .5;
    bool is_active = false;
    int iteration = 0;
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
                    if (event.key.code == sf::Keyboard::P) {
                        is_active = !is_active;
                    }

                    if (!is_active && event.key.code == sf::Keyboard::U) {
                        window.setTitle(std::to_string(++iteration));
                        gol.update();
                    }

                    if (event.key.code == sf::Keyboard::R) {
                        is_active = false;
                        iteration = 0;
                        window.setTitle("0");
                        gol.reset();
                    }
                    break;

                default:
                    break;
            }
        }

        window.clear();

        if (is_active &&
            clock.getElapsedTime().asSeconds() >= update_delay) {
            window.setTitle(std::to_string(++iteration));
            gol.update();
            clock.restart();
        }

        gol.display_grid(window);

        window.display();
    }
}
