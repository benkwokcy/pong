#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Score.hpp"
#include "Utilities.hpp"

using namespace std;

struct Score {
    Vec2 position;
    int valueInt;
    std::string valueString;
    SDL_Rect rect {};    
    TTF_Font* font {};
    SDL_Renderer* renderer {};
    SDL_Surface* surface {};
    SDL_Texture* texture {};

    Score(Vec2 position, SDL_Renderer* renderer, TTF_Font* font) : position(position), valueInt(0), font(font), renderer(renderer) { 
        regenerate();
        int width, height; SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
        rect.x = static_cast<int>(position.x);
        rect.y = static_cast<int>(position.y);
        rect.w = width;
        rect.h = height;
    }

    ~Score() {
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    Score(const Score& other) = delete;
    Score& operator=(const Score& other) = delete;
    
    Score(Score&& other) :
        position(std::move(other.position)),
        valueInt(other.valueInt),
        valueString(std::move(other.valueString)),
        rect(std::move(other.rect)),
        font(other.font),
        renderer(other.renderer),
        surface(other.surface),
        texture(other.texture)
    {
        other.renderer = nullptr;
        other.surface = nullptr;
        other.texture = nullptr;
        other.font = nullptr;
    }

    Score& operator=(Score&& other) {
        position = std::move(other.position);
        rect = std::move(other.rect);
        font = other.font; 
        valueString = std::move(other.valueString);
        valueInt = other.valueInt;
        renderer = other.renderer; 
        surface = other.surface; 
        texture = other.texture; 

        other.renderer = nullptr;
        other.font = nullptr;
        other.surface = nullptr;
        other.texture = nullptr;

        return *this;
    }

    void regenerate() {
        valueString = to_string(valueInt);
        surface = TTF_RenderText_Solid(font, valueString.data(), {0xFF, 0xFF, 0xFF, 0xFF});
        texture = SDL_CreateTextureFromSurface(renderer, surface);
    }

    void increment() {
        valueInt++;
        regenerate();
    }

    void draw() const {
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }

};