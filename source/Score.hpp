#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Utilities.hpp"

struct Score {
    SDL_Rect rect {};    
    Vec2 position;
    int valueInt;
    std::string valueString;
    TTF_Font* font {};
    SDL_Surface* surface {};
    SDL_Texture* texture {};
    SDL_Renderer* renderer {};

    Score(Vec2 position, SDL_Renderer* renderer, TTF_Font* font);
    ~Score();

    Score(const Score& other) = delete;
    Score& operator=(const Score& other) = delete;
    
    Score(Score&& other);
    Score& operator=(Score&& other);

    void regenerate();
    void increment();
    void draw() const;
};