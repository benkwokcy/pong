#ifndef BALL_H
#define BALL_H

#include "Utilities.hpp"
#include <SDL2/SDL.h>

struct World;

struct Ball {
    constexpr static float HORIZONTAL_SPEED = 5.0f;
    constexpr static float VERTICAL_SPEED = 0.75 * HORIZONTAL_SPEED;
    constexpr static int WIDTH = 15;
    constexpr static int HEIGHT = 15;
    Vec2 position;
    Vec2 velocity;
    const Vec2 initialPosition;
    const Vec2 initialVelocity;
    SDL_Rect rect {};  

    Ball(Vec2 position, Vec2 velocity);
    void reset(int sign);
    void update(World& world);
    void collide(World& world);
    void draw(SDL_Renderer* renderer) const;
};

#endif