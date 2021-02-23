#ifndef PADDLE_H
#define PADDLE_H

#include <SDL2/SDL.h>

#include "Input.hpp"
#include "Utilities.hpp"

class Paddle {
public:
    constexpr static float SPEED = 6.0f;
    constexpr static int WIDTH = 15;
    constexpr static int HEIGHT = 75;

    Paddle(Vec2 position, Vec2 velocity);

    const Vec2& getPosition() const; 

    void update(const PaddleState& paddleState);
    void draw(SDL_Renderer* renderer) const;
private:
    Vec2 position;
    Vec2 velocity;
    SDL_Rect rect {};    
};

#endif