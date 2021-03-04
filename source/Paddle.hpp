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

    Paddle(Vec2 position, Vec2 velocity, bool isAIControlled);
    const Vec2& getPosition() const; 
    const Vec2& getVelocity() const; 
    void update(const World& world, const Input& input);
    void draw(SDL_Renderer* renderer) const;
private:
    using controllerFunctionPointer = void (Paddle::*)(const World& world, const Input& input);

    Vec2 position;
    Vec2 velocity;
    SDL_Rect rect {};
    controllerFunctionPointer controller;

    void aiController(const World& world, const Input& input);
    void playerController(const World& world, const Input& input);
};