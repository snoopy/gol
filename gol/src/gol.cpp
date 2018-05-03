#include "gol.h"

#include <SFML/Graphics.hpp>

#include <cstddef>
#include <ctime>
#include <random>
#include <vector>

Gol::Gol(int width_, int height_)
    : width{width_}
    , height{height_}
    , grid_current{}
    , grid_next{}
    , grid_visual{}
    , rng{}
{
    std::random_device rd;
    rng.seed(rd());

    reset();
}

void Gol::display_grid(sf::RenderWindow& window) const {
    window.draw(&grid_visual[0], grid_visual.size(), sf::Points);
}

void Gol::update() {
    grid_current.swap(grid_next);
    for (int m = 0; m < height; ++m) {
        for (int n = 0; n < width; ++n) {
            apply_rules(count_neighbors(m, n), m, n);
        }
    }
}

void Gol::reset() {
    grid_current.clear();
    grid_current.resize(static_cast<std::size_t>(height),
        std::vector<bool>(width));
    grid_next.clear();
    grid_next.resize(static_cast<std::size_t>(height),
        std::vector<bool>(width));
    init_visuals();
    seed_grid();
}

void Gol::init_visuals() {
    grid_visual.clear();
    grid_visual.resize(width * height);

    int pos = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            grid_visual[pos].position =
                sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
            // postfix intended
            grid_visual[pos++].color = visual_dead;
        }
    }
}

void Gol::seed_grid() {
    std::uniform_int_distribution<int> m_axis(0, height - 1);
    std::uniform_int_distribution<int> n_axis(0, width - 1);
    std::uniform_int_distribution<int> cells(width * height / 2,
                                            width * height);

    int initial_cell_nr = cells(rng);
    while (initial_cell_nr > 0) {
        std::size_t m = m_axis(rng);
        std::size_t n = n_axis(rng);
        if (!grid_next[m][n]) {
            grid_next[m][n] = true;
            grid_visual[m * width + n].color = visual_alive;
            --initial_cell_nr;
        }
    }
}

int Gol::count_neighbors(int m_origin, int n_origin) const {
    int neighbors = 0;
    for (int m_current = m_origin - 1; m_current <= m_origin + 1; ++m_current) {
        for (int n_current = n_origin - 1; n_current <= n_origin + 1; ++n_current) {
            if (m_current < 0 || m_current >= height ||
                n_current < 0 || n_current >= width) {
                continue;
            }

            if (m_current == m_origin && n_current == n_origin) {
                continue;
            }

            if (grid_current[m_current][n_current]) {
                if (++neighbors > 3) {
                    return neighbors;
                }
            }
        }
    }
    return neighbors;
}

void Gol::apply_rules(int neighbors, int m, int n) {
    grid_next[m][n] = grid_current[m][n];

    // Any live cell with fewer than two live neighbors dies,
    // as if caused by under population.
    if (grid_current[m][n] && neighbors < 2) {
        grid_next[m][n] = false;
        grid_visual[m * width + n].color = visual_dead;
    }

    // Any live cell with two or three live neighbors lives on
    if (grid_current[m][n] && (neighbors == 2 || neighbors == 3)) {
        grid_next[m][n] = true;
        grid_visual[m * width + n].color = visual_alive;
    }

    // Any live cell with more than three live neighbors dies,
    // as if by overpopulation.
    if (grid_current[m][n] && neighbors > 3) {
        grid_next[m][n] = false;
        grid_visual[m * width + n].color = visual_dead;
    }

    // Any dead cell with exactly three live neighbors becomes a live cell,
    // as if by reproduction.
    if (!grid_current[m][n] && neighbors == 3) {
        grid_next[m][n] = true;
        grid_visual[m * width + n].color = visual_alive;
    }
}
