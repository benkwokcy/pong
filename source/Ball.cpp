#include <stdexcept>
#include <iostream>

#include "Ball.hpp"
#include "Utilities.hpp"
#include "World.hpp"
#include "Window.hpp"
#include "Collision.hpp"

/*** CONSTRUCTORS ***/

Ball::Ball(Vec2 position, Vec2 velocity) : position(position), velocity(velocity), initialPosition(position), initialVelocity(velocity) {
    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
    rect.w = WIDTH;
    rect.h = HEIGHT;
}

/*** GETTERS ***/

const Vec2& Ball::getPosition() const { return position; }

/*** PUBLIC METHODS ***/

void Ball::draw(SDL_Renderer* renderer) const {
    SDL_RenderFillRect(renderer, &rect);
}

void Ball::update(World& world) {
    collide(world);
    position += velocity;
    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
}

/*** PRIVATE METHODS ***/

bool Ball::collide(World& world) {
    return (collideWall(world)) || (collidePaddle(world, world.playerPaddle)) || (collidePaddle(world, world.aiPaddle));
}

bool Ball::collideWall(World& world) {
    auto collisionType = checkWallCollision(*this);
    switch (collisionType) {
        case LEFT:
            world.scores[0].increment();
            reset(-1);
            return true;
        case RIGHT:
            world.scores[1].increment();
            reset(1);
            return true;
        case TOP:
            velocity.y *= -1;
            position.y = 0.0;
            world.audio.playWallHit();
            return true;
        case BOTTOM:
            velocity.y *= -1;
            position.y = Window::HEIGHT - HEIGHT;
            world.audio.playWallHit();
            return true;
        case NONE:
            return false;
    }
}

bool Ball::collidePaddle(const World& world, const Paddle& paddle) {
    auto [collisionType, penetration] = checkObjectCollision(paddle, *this);
    if (collisionType == NONE) return false;

    cout << "Hit detected: " << collisionType << endl;

    switch (collisionType) {
        case TOP:
            velocity.y *= -1.0f;
            position.y += penetration;
            break;
        case BOTTOM:
            velocity.y *= -1.0f; 
            position.y -= penetration;
            break;
        case LEFT:
            velocity.x = SPEED;
            position.x += penetration;
            break;
        case RIGHT:
            velocity.x = -SPEED;
            position.x -= penetration;
            break;
        default:
            throw runtime_error("Unhandled collision type.");
    }

    world.audio.playPaddleHit();
    return true;
}

void Ball::reset(int sign) {
    position = initialPosition;
    velocity = initialVelocity;
    velocity.x *= static_cast<float>(sign);
    SDL_Delay(100);
}