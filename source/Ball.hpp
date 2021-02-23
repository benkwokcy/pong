#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>

#include "Utilities.hpp"

struct World;

class Ball {
public:
    constexpr static float HORIZONTAL_SPEED = 5.0f;
    constexpr static float VERTICAL_SPEED = 0.75 * HORIZONTAL_SPEED;
    constexpr static int WIDTH = 15;
    constexpr static int HEIGHT = 15;

    Ball(Vec2 position, Vec2 velocity);
    
    void update(World& world);
    void draw(SDL_Renderer* renderer) const;
private:
    Vec2 position;
    Vec2 velocity;
    SDL_Rect rect {};  
    const Vec2 initialPosition;
    const Vec2 initialVelocity;

    void collide(World& world);
    void reset(int sign);
};

#endif