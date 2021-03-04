#pragma once

#include <stdexcept>

#include <SDL2/SDL.h>

#include "Window.hpp"

enum CollisionType {
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
    NONE
};

template <class T>
CollisionType checkWallCollision(const T& object) {
    const auto position = object.getPosition();

    const auto objectLeft = position.x;
    const auto objectRight = objectLeft + T::WIDTH;
    const auto objectTop = position.y;
    const auto objectBottom = objectTop + T::HEIGHT;

    // don't act until it moves out of bounds on the left or right wall.
    if (objectRight < 0.0f) {
        return LEFT;
    } else if (objectLeft > Window::WIDTH) {
        return RIGHT;
    // act as soon as it touches top or bottom wall
    } else if (objectTop < 0.0f) { 
        return TOP;
    } else if (objectBottom > Window::HEIGHT) {
        return BOTTOM;
    } else {
        return NONE;
    }
}

// This is the collision from B's perspective. ex. if A hits the top of B, we say it is a BOTTOM collision.
// Returns the collision type and the amount of penetration.
template <class A, class B>
pair<CollisionType, float> checkObjectCollision(const A& a, const B& b) {
    const auto aPosition = a.getPosition();
    const auto aLeft = aPosition.x;
    const auto aRight = aLeft + A::WIDTH;
    const auto aTop = aPosition.y;
    const auto aBottom = aTop + A::HEIGHT;

    auto& bPosition = b.getPosition();
    const auto bLeft = bPosition.x;
    const auto bRight = bLeft + B::WIDTH;
    const auto bTop = bPosition.y;
    const auto bBottom = bTop + B::HEIGHT;

    float dx = (aLeft + A::WIDTH / 2.0f) - (bLeft + B::WIDTH / 2.0f);
    float dy = (aTop + A::HEIGHT / 2.0f) - (bTop + B::HEIGHT / 2.0f);
    float width = (A::WIDTH + B::WIDTH) / 2.0f;
    float height = (A::HEIGHT + B::HEIGHT) / 2.0f;
    float crossWidth = width * dy;
    float crossHeight = height * dx;
    CollisionType collision = NONE;

    if (abs(dx) <= width && abs(dy) <= height) {
        if (crossWidth > crossHeight) {
            collision = (crossWidth > (-crossHeight)) ? BOTTOM : LEFT;
        } else {
            collision = (crossWidth > -(crossHeight)) ? RIGHT : TOP;
        }
    }

    return { collision, 0.0f };
}