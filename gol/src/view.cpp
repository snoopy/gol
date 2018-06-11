#pragma once

#include "view.h"

#include <string>

namespace GameOfLife  {

View::View(int const width_, int const height_, sf::RenderWindow& win_)
    : pixmap{std::vector<uint_fast8_t>(width_ * height_ * rgba_quad)}
    , texture{}
    , sprite{}
    , win{win_}
{
    for (int i = 0; i < width_ * height_ * rgba_quad; i += rgba_quad) {
        pixmap[i + offset_r] = 255;
        pixmap[i + offset_g] = 255;
        pixmap[i + offset_b] = 255;
        pixmap[i + offset_a] = 0;
    }

    texture.create(width_, height_);
    sprite.setTexture(texture);
    sprite.setPosition(0, 0);
}

void View::update(int pos, bool const state, std::uint64_t const iterations_) {
    pos *= rgba_quad;
    pos += offset_a;
    pixmap[pos] = state ? 255 : 0;
    iterations = iterations_;
    model_was_updated = true;
}

void View::display() {
    if (model_was_updated) {
        texture.update(&pixmap[0]);
        model_was_updated = false;
    }

    win.setTitle(std::to_string(iterations));
    win.draw(sprite);
}

}
