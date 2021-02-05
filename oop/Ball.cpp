#include "Ball.hpp"
#include "Utilities.hpp"
#include "World.hpp"

Ball::Ball(Vec2 position, Vec2 velocity) : position(position), velocity(velocity), initialPosition(position), initialVelocity(velocity) {
    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
    rect.w = WIDTH;
    rect.h = HEIGHT;
}

void Ball::reset(int sign) {
    position = initialPosition;
    velocity = initialVelocity;
    velocity.x *= static_cast<float>(sign);
    SDL_Delay(100);
}

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
    const auto ballLeft = position.x;
    const auto ballRight = ballLeft + WIDTH;
    const auto ballTop = position.y;
    const auto ballBottom = ballTop + HEIGHT;

    // WALL COLLISION
    if (ballRight < 0.0f) {
        world.scores[0].increment();
        reset(-1);
        return;
    } else if (ballLeft > Window::WIDTH) {
        world.scores[1].increment();
        reset(1);
        return;
    } else if (ballTop < 0.0f) { 
        velocity.y *= -1;
        position.y = 0.0;
        world.audio.playWallHit();
        return;
    } else if (ballBottom > Window::HEIGHT) {
        velocity.y *= -1;
        position.y = Window::HEIGHT - HEIGHT;
        world.audio.playWallHit();
        return;
    }

    // PADDLE COLLISION
    for (auto& paddle : world.paddles) {
        const auto paddleLeft = paddle.position.x;
        const auto paddleRight = paddleLeft + Paddle::WIDTH;
        const auto paddleTop = paddle.position.y;
        const auto paddleBottom = paddleTop + Paddle::HEIGHT;

        if (ballLeft >= paddleRight) continue;
        if (ballRight <= paddleLeft) continue;
        if (ballTop >= paddleBottom) continue;
        if (ballBottom <= paddleTop) continue;

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
        
        return;
    }
}