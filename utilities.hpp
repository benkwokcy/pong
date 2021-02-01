#pragma once

// Pair of floats that do memberwise addition and multiplication
struct Vec2 {
    Vec2(): x(0.0f), y(0.0f) {}
    Vec2(float x, float y): x(x), y(y) {}
    Vec2 operator+(Vec2 const& other) { return Vec2(x + other.x, y + other.y); }
    Vec2 operator*(const float scale) { return Vec2(x * scale, y * scale); }
    float x, y;
};
