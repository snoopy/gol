#pragma once

#include "view.h"

#include <cstdint>
#include <random>
#include <vector>

namespace GameOfLife {

class Model {
public:
    Model(int const width_, int const height_, View& view_);

    void update();
    void reset();

private:
    void init_visuals();
    void seed_grid();
    int count_neighbors(int const m_origin, int const n_origin) const;
    void check_rules(int const pos, int const neighbors);
    void apply_rules(int pos, bool const state);

    int width;
    int height;
    std::vector<bool> grid_current;
    std::vector<bool> grid_next;
    View& view;
    std::mt19937 rng;
    std::uint64_t iterations = 0;
    static constexpr bool cell_alive = true;
    static constexpr bool cell_dead = false;
};

}
