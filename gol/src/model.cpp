#include "model.h"
#include "view.h"

#include <cstddef>
#include <cstdint>
#include <ctime>
#include <random>
#include <vector>

namespace GameOfLife {

Model::Model(int const width_, int const height_, View& view_)
    : width{width_}
    , height{height_}
    , grid_current{}
    , grid_next{}
    , view{view_}
    , rng{}
{
    std::random_device rd;
    rng.seed(rd());

    reset();
}

void Model::update() {
    grid_current.swap(grid_next);

    ++iterations;

    for (int m = 0; m < height; ++m) {
        for (int n = 0; n < width; ++n) {
            check_rules(width * m + n, count_neighbors(m, n));
        }
    }
}

void Model::reset() {
    grid_current.clear();
    grid_current.resize(static_cast<std::size_t>(width * height));
    grid_next.clear();
    grid_next.resize(static_cast<std::size_t>(width * height));
    seed_grid();
    iterations = 0;
}

void Model::seed_grid() {
    std::uniform_int_distribution<int> pos_dist(0, width * height);
    std::uniform_int_distribution<int> cells(width * height / 2,
                                            width * height);

    int initial_cell_nr = cells(rng);
    while (initial_cell_nr > 0) {
        std::size_t pos = pos_dist(rng);
        if (grid_next[pos] == cell_dead) {
            grid_next[pos] = cell_alive;
            --initial_cell_nr;
            view.update(pos, cell_alive, 0U);
        }
    }
}

int Model::count_neighbors(int const m_origin, int const n_origin) const {
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

            if (grid_current[width * m_current + n_current] == cell_alive) {
                if (++neighbors > 3) {
                    return neighbors;
                }
            }
        }
    }
    return neighbors;
}

void Model::check_rules(int const pos, int const neighbors) {
    apply_rules(pos, grid_current[pos]);

    // Any live cell with fewer than two live neighbors dies,
    // as if caused by under population.
    if (grid_current[pos] == cell_alive && neighbors < 2) {
        apply_rules(pos, cell_dead);
    }

    // Any live cell with two or three live neighbors lives on
    if (grid_current[pos] == cell_alive && (neighbors == 2 || neighbors == 3)) {
        apply_rules(pos, cell_alive);
    }

    // Any live cell with more than three live neighbors dies,
    // as if by overpopulation.
    if (grid_current[pos] == cell_alive && neighbors > 3) {
        apply_rules(pos, cell_dead);
    }

    // Any dead cell with exactly three live neighbors becomes a live cell,
    // as if by reproduction.
    if (grid_current[pos] == cell_dead && neighbors == 3) {
        apply_rules(pos, cell_alive);
    }
}

void Model::apply_rules(int pos, bool const state) {
    grid_next[pos] = state;

    view.update(pos, state, iterations);
}

}
