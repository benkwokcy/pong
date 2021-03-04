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

// This is the collision from B's perspective. ex. if A is on top B, we say it is a TOP collision.
// Returns the collision type and the amount of penetration.
// https://stackoverflow.com/questions/29861096/detect-which-side-of-a-rectangle-is-colliding-with-another-rectangle
template <class A, class B>
pair<CollisionType, float> checkObjectCollision(const A& a, const B& b) {
    const auto aPosition = a.getPosition();
    const auto aLeft = aPosition.x;
    const auto aRight = aPosition.x + A::WIDTH;
    const auto aTop = aPosition.y;
    const auto aBottom = aPosition.y + A::HEIGHT;

    const auto bPosition = b.getPosition();
    const auto bLeft = bPosition.x;
    const auto bRight = bPosition.x + B::WIDTH;
    const auto bTop = bPosition.y;
    const auto bBottom = bPosition.y + B::HEIGHT;

    const float dx = (aLeft + A::WIDTH / 2.0f) - (bLeft + B::WIDTH / 2.0f);
    const float dy = (aTop + A::HEIGHT / 2.0f) - (bTop + B::HEIGHT / 2.0f);
    const float width = (A::WIDTH + B::WIDTH) / 2.0f;
    const float height = (A::HEIGHT + B::HEIGHT) / 2.0f;
    const float crossWidth = width * dy;
    const float crossHeight = height * dx;

    CollisionType collision = NONE;
    float penetration = 0.0f;

    if (abs(dx) <= width && abs(dy) <= height) {
        if (crossWidth > crossHeight) {
            if ((crossWidth > (-crossHeight))) {
                collision = BOTTOM;
                penetration = bBottom - aTop;
            } else {
                collision = LEFT;
                penetration = aRight - bLeft;
            }
        } else {
            if (crossWidth > -(crossHeight)) {
                collision = RIGHT;
                penetration = bRight - aLeft;
            } else {
                collision = TOP;
                penetration = aBottom - bTop;
            }
        }
    }

    return { collision, penetration };
}