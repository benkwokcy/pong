#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>

#include "Utilities.hpp"

struct World;
class Paddle;

class Ball {
public:
    constexpr static float HORIZONTAL_SPEED = 6.0f;
    constexpr static float VERTICAL_SPEED = 1.0f * HORIZONTAL_SPEED;
    constexpr static int WIDTH = 15;
    constexpr static int HEIGHT = 15;

    Ball(Vec2 position, Vec2 velocity);

    const Vec2& getPosition() const;

    void update(World& world);
    void draw(SDL_Renderer* renderer) const;
private:
    Vec2 position;
    Vec2 velocity;
    SDL_Rect rect {};  
    const Vec2 initialPosition;
    const Vec2 initialVelocity;

    void collide(World& world);
    bool collideWall(World& world);
    bool collidePaddle(const World& world, const Paddle& paddle);
    void reset(int sign);
};

#endif