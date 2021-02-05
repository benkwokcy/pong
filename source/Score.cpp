#include "Score.hpp"
#include "Utilities.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

Score::Score(Vec2 position, SDL_Renderer* renderer, TTF_Font* font) : position(position), valueInt(0), font(font), renderer(renderer) { 
    regenerate();
    int width, height; SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
    rect.w = width;
    rect.h = height;
}

Score::~Score() {
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

Score::Score(Score&& other) :
    position(std::move(other.position)),
    valueInt(other.valueInt),
    valueString(std::move(other.valueString)),
    font(other.font)
{
    rect = std::move(other.rect);
    renderer = other.renderer; other.renderer = nullptr;
    surface = other.surface; other.surface = nullptr;
    texture = other.texture; other.texture = nullptr;
    other.font = nullptr;
}

Score& Score::operator=(Score&& other) {
    position = std::move(other.position);
    rect = std::move(other.rect);
    renderer = other.renderer; other.renderer = nullptr;
    font = other.font; other.font = nullptr;
    surface = other.surface; other.surface = nullptr;
    texture = other.texture; other.texture = nullptr;
    valueString = std::move(other.valueString);
    valueInt = other.valueInt;
    return *this;
}

void Score::regenerate() {
    valueString = to_string(valueInt);
    surface = TTF_RenderText_Solid(font, valueString.data(), {0xFF, 0xFF, 0xFF, 0xFF});
    texture = SDL_CreateTextureFromSurface(renderer, surface);
}

void Score::increment() {
    valueInt++;
    regenerate();
}

void Score::draw() const {
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}