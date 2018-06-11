#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

namespace GameOfLife {

class View {
public:
    View(int const width, int const height, sf::RenderWindow& win_);

    void update(int pos, bool const state, std::uint64_t const iterations_);
    void display();

private:
    std::vector<std::uint_fast8_t> pixmap;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::RenderWindow& win;
    std::uint64_t iterations = 0;
    bool model_was_updated = false;
    static constexpr int offset_r = 0;
    static constexpr int offset_g = 1;
    static constexpr int offset_b = 2;
    static constexpr int offset_a = 3;
    static constexpr int rgba_quad = 4;
};

}
