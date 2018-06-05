#include <SFML/Graphics.hpp>

#include <cstdint>
#include <random>
#include <vector>

namespace GameOfLife {

class Gol {
public:
    Gol(int width_, int height_);

    void display_grid(sf::RenderWindow& window) const;
    void update();
    void reset();

private:
    void init_visuals();
    void seed_grid();
    int count_neighbors(int m_origin, int n_origin) const;
    void apply_rules(int pos, int neighbors);

    int width;
    int height;
    std::vector<std::uint_fast16_t> grid_current;
    std::vector<std::uint_fast16_t> grid_next;
    std::vector<sf::Vertex> grid_visual;
    std::mt19937 rng;
    sf::Color visual_alive = sf::Color::White;
    sf::Color visual_dead = sf::Color::Black;
};
}
