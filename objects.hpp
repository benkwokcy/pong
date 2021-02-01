#pragma once

#include "utilities.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct Object {
    Object(Vec2 position) : position(position) {
        rect.x = static_cast<int>(position.x);
        rect.y = static_cast<int>(position.y);
    }

    virtual void draw(SDL_Renderer* renderer) = 0;

    Vec2 position;
    SDL_Rect rect {};    
};

struct MovingObject : public Object {
    MovingObject(Vec2 position, Vec2 velocity) : Object(position), velocity(velocity) {}

    virtual void update(float dt) = 0;

    Vec2 velocity;
};

struct Ball : public Object {
    Ball(Vec2 position) : Object(position) {
        rect.w = WIDTH;
        rect.h = HEIGHT;
    }

    void draw(SDL_Renderer* renderer) {
        rect.x = static_cast<int>(position.x);
        rect.y = static_cast<int>(position.y);
        SDL_RenderFillRect(renderer, &rect);
    }

    constexpr static int WIDTH = 15;
    constexpr static int HEIGHT = 15;
};

struct Paddle : public MovingObject {
    Paddle(Vec2 position, Vec2 velocity) : MovingObject(position, velocity) {
        rect.w = WIDTH;
        rect.h = HEIGHT;
    }

    void update(float dt) {
        position = velocity * dt;
        std::clamp(position.y, 0.0f, static_cast<float>(WINDOW_HEIGHT - HEIGHT));
    }

    void draw(SDL_Renderer* renderer) {
        rect.y = static_cast<int>(position.y);
        SDL_RenderFillRect(renderer, &rect);
    }

    constexpr static int WIDTH = 15;
    constexpr static int HEIGHT = 75;
};

struct Score : public Object {
    Score(Vec2 position, SDL_Renderer* renderer, TTF_Font* font) : Object(position), font(font) { 
        surface = TTF_RenderText_Solid(font, "0", {0xFF, 0xFF, 0xFF, 0xFF});
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        int width, height; 
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
        rect.w = width;
        rect.h = height;
    }

    ~Score() {
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    void draw(SDL_Renderer* renderer) {
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }

    TTF_Font* font {};
    SDL_Surface* surface {};
    SDL_Texture* texture {};
};