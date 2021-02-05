#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Utilities.hpp"

struct Score {
    Vec2 position;
    int valueInt;
    std::string valueString;
    SDL_Rect rect {};    
    TTF_Font* font {};
    SDL_Renderer* renderer {};
    SDL_Surface* surface {};
    SDL_Texture* texture {};

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