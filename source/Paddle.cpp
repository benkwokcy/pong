#include "Paddle.hpp"
#include "Utilities.hpp"
#include "Window.hpp"
#include "Input.hpp"
#include "World.hpp"
#include <SDL2/SDL.h>

/*** CONSTRUCTORS ***/

Paddle::Paddle(Vec2 position, Vec2 velocity, bool isAIControlled) : position(position), velocity(velocity) {
    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
    rect.w = WIDTH;
    rect.h = HEIGHT;
    controller = isAIControlled ? &Paddle::aiController : &Paddle::playerController;
}

/*** GETTERS ***/

const Vec2& Paddle::getPosition() const {
    return position;
}

const Vec2& Paddle::getVelocity() const {
    return velocity;
}

/*** PUBLIC METHODS ***/

void Paddle::update(const World& world, const Input& input) {
    (this->*controller)(world, input);
    position.y += velocity.y;
    position.y = std::clamp(position.y, 0.0f, static_cast<float>(Window::HEIGHT - HEIGHT));
    rect.y = static_cast<int>(position.y);
}

void Paddle::draw(SDL_Renderer* renderer) const {
    SDL_RenderFillRect(renderer, &rect);
}

/*** PRIVATE METHODS ***/

void Paddle::aiController(const World& world, [[maybe_unused]] const Input& input) {
    float paddleCenter = position.y + (HEIGHT / 2.0);
    float ballCenter = world.ball.getPosition().y;

    if (abs(paddleCenter - ballCenter) < Paddle::HEIGHT * 0.45f) return;

    if (paddleCenter > ballCenter) {
        velocity.y = -SPEED;
    } else if (paddleCenter < ballCenter) {
        velocity.y = SPEED;
    } else {
        velocity.y = 0.0f;
    }
}

void Paddle::playerController([[maybe_unused]] const World& world, const Input& input) {
    if (input.paddleUp) {
        velocity.y = -SPEED;
    } else if (input.paddleDown) {
        velocity.y = SPEED;
    } else {
        velocity.y = 0.0f;
    }
}