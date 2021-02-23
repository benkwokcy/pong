#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Utilities.hpp"

using namespace std;

class Text {
public:
    Text(Vec2 position, SDL_Renderer* renderer, TTF_Font* font, string content) : position(position), valueString(content), font(font), renderer(renderer) { 
        generate();
        int width, height; SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
        position.x -= width / 2;
        position.y -= height / 2;
        rect.x = static_cast<int>(position.x);
        rect.y = static_cast<int>(position.y);
        rect.w = width;
        rect.h = height;
    }

    virtual ~Text() {
        clear();
    }

    Text(const Text& other) = delete;
    Text& operator=(const Text& other) = delete;
    
    Text(Text&& other) :
        position(std::move(other.position)),
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

    Text& operator=(Text&& other) {
        position = std::move(other.position);
        valueString = std::move(other.valueString);
        rect = std::move(other.rect);
        font = other.font; 
        renderer = other.renderer; 
        surface = other.surface; 
        texture = other.texture; 

        other.renderer = nullptr;
        other.font = nullptr;
        other.surface = nullptr;
        other.texture = nullptr;

        return *this;
    }

    void draw() const {
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }

protected:
    Vec2 position;
    std::string valueString;
    SDL_Rect rect {};    
    TTF_Font* font {};
    SDL_Renderer* renderer {};
    SDL_Surface* surface {};
    SDL_Texture* texture {};

    void clear() {
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    void generate() {
        surface = TTF_RenderText_Solid(font, valueString.data(), {0xFF, 0xFF, 0xFF, 0xFF});
        texture = SDL_CreateTextureFromSurface(renderer, surface);
    }

    void regenerate() {
        clear();
        generate();
    }
};