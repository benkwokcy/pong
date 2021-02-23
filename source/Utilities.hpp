#pragma once

#include <iostream>

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
