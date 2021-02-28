#pragma once

#include <SDL2/SDL.h>

#include "Utilities.hpp"

struct World;
struct Input;

class Paddle {
public:
    constexpr static float SPEED = 6.5f;
    constexpr static int WIDTH = 15;
    constexpr static int HEIGHT = 75;

    Paddle(Vec2 position, Vec2 velocity);

    const Vec2& getPosition() const; 

    void update(const World& world, const Input& input, bool isAI);
    void draw(SDL_Renderer* renderer) const;
private:
    Vec2 position;
    Vec2 velocity;
    SDL_Rect rect {};    

    void updateAI(const World& world, const Input& input);
    void updatePlayer(const World& world, const Input& input);
};