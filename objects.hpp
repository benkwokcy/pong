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

struct Paddle : public Object {
    Paddle(Vec2 position) : Object(position) {
        rect.w = WIDTH;
        rect.h = HEIGHT;
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
        surface = TTF_RenderText_Solid(font, "0", {0xFF, 0xFF, 0xFF, 0xFF}); // create a new surface with the text "0"
        texture = SDL_CreateTextureFromSurface(renderer, surface); // a texture is a surface that is store in the GPU's VRAM
        int width, height;
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height); // get the width/height of the texture
        rect.w = width;
        rect.h = height;
    }

    ~Score() {
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    void draw(SDL_Renderer* renderer) {
        SDL_RenderCopy(renderer, texture, nullptr, &rect); // Use our renderer to draw the rect portion of texture onto our main surface.
    }

    TTF_Font* font {};
    SDL_Surface* surface {};
    SDL_Texture* texture {};
};