#ifndef PADDLE_H
#define PADDLE_H

#include <SDL2/SDL.h>
#include "Input.hpp"
#include "Utilities.hpp"

struct Paddle {
    constexpr static float SPEED = 6.0f;
    constexpr static int WIDTH = 15;
    constexpr static int HEIGHT = 75;

    Vec2 position;
    Vec2 velocity;
    SDL_Rect rect {};    

    Paddle(Vec2 position, Vec2 velocity);

    void update(const PaddleState& paddleState);
    void draw(SDL_Renderer* renderer) const;
};

#endif