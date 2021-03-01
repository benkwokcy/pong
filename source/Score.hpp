#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Text.hpp"

using namespace std;

// A text element that displays an incrementable integer.
class Score : public Text {
public:
    Score(Vec2 position, SDL_Renderer* renderer, TTF_Font* font, string content) : 
        Text(position, renderer, font, content), valueInt(0) 
    {}

    Score(Score&& other) : Text(move(other)) {
        valueInt = other.valueInt;
    }

    Score& operator=(Score&& other) {
        Text::operator=(move(other));
        valueInt = other.valueInt;
        return *this;
    }

    void increment() {
        valueString = to_string(++valueInt);
        regenerate();
    }

private:
    int valueInt;
};