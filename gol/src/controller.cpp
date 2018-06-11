#include "controller.h"
#include "model.h"
#include "view.h"

namespace GameOfLife {

Controller::Controller(int const width, int const height, sf::RenderWindow& win)
    : view{width, height, win}
    , model{width, height, view}
{}

void Controller::update_model() {
    if (is_active) {
        model.update();
    }
}

void Controller::display_view() {
    view.display();
}

void Controller::on_keypress(sf::Event const& event) {
    if (event.key.code == sf::Keyboard::P) {
        is_active = !is_active;
    }

    if (!is_active && event.key.code == sf::Keyboard::U) {
        model.update();
    }

    if (event.key.code == sf::Keyboard::R) {
        model.reset();
    }
}

}
