#pragma once

constexpr int WINDOW_WIDTH = 640;
constexpr int WINDOW_HEIGHT = 480;

// A pair of floats that supports addition and multiplication
struct Vec2 {
    Vec2(): x(0.0f), y(0.0f) {}
    Vec2(float x, float y): x(x), y(y) {}

    Vec2 operator+(Vec2 const& other) const { 
        return Vec2(x + other.x, y + other.y); 
    }
    
    Vec2& operator+=(Vec2 const& other) { 
        x += other.x;
        y += other.y;
        return *this; 
    }

    Vec2 operator*(const float scale) const { 
        return Vec2(x * scale, y * scale); 
    }

    float x, y;
};
