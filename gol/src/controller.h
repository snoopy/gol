#pragma once

#include "model.h"
#include "view.h"

#include <SFML/System.hpp>

namespace GameOfLife {

class Controller {
public:
    Controller(int const width, int const height, sf::RenderWindow& win);

    void update_model();
    void display_view();
    void on_keypress(sf::Event const& event);

private:
    View view;
    Model model;
    bool is_active = false;
};

}
