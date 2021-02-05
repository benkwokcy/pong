#pragma once

#include <iostream>
#include <SDL2/SDL.h>

// Allows convenient arithmetic operations on a pair of floats.
struct Vec2 {
    Vec2(): x(0.0f), y(0.0f) {}
    Vec2(float x, float y): x(x), y(y) {}
    
    Vec2& operator+=(const Vec2& other) { 
        x += other.x;
        y += other.y;
        return *this; 
    }

    float x, y;
};

// Crash if code is equal to error code
template <typename A, typename B>
void verify(const A actualCode, const B errorCode) {
    if (actualCode == static_cast<A>(errorCode)) {
        std::cout << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
}
