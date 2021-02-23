#include "Ball.hpp"
#include "Utilities.hpp"
#include "World.hpp"
#include "Window.hpp"

Ball::Ball(Vec2 position, Vec2 velocity) : position(position), velocity(velocity), initialPosition(position), initialVelocity(velocity) {
    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
    rect.w = WIDTH;
    rect.h = HEIGHT;
}

const Vec2& Ball::getPosition() const { return position; }

void Ball::draw(SDL_Renderer* renderer) const {
    SDL_RenderFillRect(renderer, &rect);
}

void Ball::update(World& world) {
    collide(world);
    position += velocity;
    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
}

void Ball::collide(World& world) {
    if (collideWall(world)) return;
    if (collidePaddle(world, world.playerPaddle)) return;
    if (collidePaddle(world, world.aiPaddle)) return;
}

bool Ball::collideWall(World& world) {
    const auto ballLeft = position.x;
    const auto ballRight = ballLeft + WIDTH;
    const auto ballTop = position.y;
    const auto ballBottom = ballTop + HEIGHT;

    // WALL COLLISION
    if (ballRight < 0.0f) {
        world.scores[0].increment();
        reset(-1);
        return true;
    } else if (ballLeft > Window::WIDTH) {
        world.scores[1].increment();
        reset(1);
        return true;
    } else if (ballTop < 0.0f) { 
        velocity.y *= -1;
        position.y = 0.0;
        world.audio.playWallHit();
        return true;
    } else if (ballBottom > Window::HEIGHT) {
        velocity.y *= -1;
        position.y = Window::HEIGHT - HEIGHT;
        world.audio.playWallHit();
        return true;
    }

    return false;
}

bool Ball::collidePaddle(const World& world, const Paddle& paddle) {
    const auto ballLeft = position.x;
    const auto ballRight = ballLeft + WIDTH;
    const auto ballTop = position.y;
    const auto ballBottom = ballTop + HEIGHT;

    auto& paddlePosition = paddle.getPosition();
    const auto paddleLeft = paddlePosition.x;
    const auto paddleRight = paddleLeft + Paddle::WIDTH;
    const auto paddleTop = paddlePosition.y;
    const auto paddleBottom = paddleTop + Paddle::HEIGHT;

    if (ballLeft >= paddleRight) return false;
    if (ballRight <= paddleLeft) return false;
    if (ballTop >= paddleBottom) return false;
    if (ballBottom <= paddleTop) return false;

    const auto paddleLower = paddleTop + (2.0f / 3.0f * Paddle::HEIGHT);
    const auto paddleUpper = paddleTop + (1.0f / 3.0f * Paddle::HEIGHT);

    if (ballTop < paddleUpper) {
        velocity.y = Ball::VERTICAL_SPEED; 
    } else if (ballBottom < paddleLower) {
        velocity.y = -Ball::VERTICAL_SPEED;
    }

    if (velocity.x > 0.0f) {
        position.x -= ballRight - paddleLeft; 
    } else {
        position.x += paddleRight - ballLeft;
    }

    velocity.x *= -1;

    world.audio.playPaddleHit();

    return true;
}

void Ball::reset(int sign) {
    position = initialPosition;
    velocity = initialVelocity;
    velocity.x *= static_cast<float>(sign);
    SDL_Delay(100);
}