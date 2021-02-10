#include "Paddle.hpp"
#include "Utilities.hpp"
#include "Window.hpp"
#include "Input.hpp"
#include <SDL2/SDL.h>

Paddle::Paddle(Vec2 position, Vec2 velocity) : position(position), velocity(velocity) {
    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
    rect.w = WIDTH;
    rect.h = HEIGHT;
}

void Paddle::update(const PaddleState& paddleState) {
    if (paddleState.up) {
        velocity.y = -SPEED;
    } else if (paddleState.down) {
        velocity.y = SPEED;
    } else {
        velocity.y = 0.0f;
    }

    position.y += velocity.y;
    position.y = std::clamp(position.y, 0.0f, static_cast<float>(Window::HEIGHT - HEIGHT));
    rect.y = static_cast<int>(position.y);
}

void Paddle::draw(SDL_Renderer* renderer) const {
    SDL_RenderFillRect(renderer, &rect);
}