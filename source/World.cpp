#include <vector>

#include "Window.hpp"
#include "World.hpp"
#include "Ball.hpp"
#include "Score.hpp"
#include "Paddle.hpp"
#include "Input.hpp"

using namespace std;

World::World(const Window& window) : 
    ball(Vec2(Window::WIDTH / 2.0f - Ball::WIDTH / 2.0f, Window::HEIGHT / 2.0f - Ball::HEIGHT / 2.0f), Vec2(Ball::SPEED, 0.0f)),
    playerPaddle(Vec2(50.0f, Window::HEIGHT / 2.0f - Paddle::HEIGHT / 2.0f), Vec2(0.0f, 0.0f), false),
    aiPaddle(Vec2(Window::WIDTH - 50.0f, Window::HEIGHT / 2.0f - Paddle::HEIGHT / 2.0f), Vec2(0.0f, 0.0f), true),
    pauseText(Vec2(Window::WIDTH / 2.0f, Window::HEIGHT / 2.0f), window.renderer, window.scoreFont, "PAUSED")
{
    scores.emplace_back(Vec2(Window::WIDTH * 0.75f, 20.0f), window.renderer, window.scoreFont, "0");
    scores.emplace_back(Vec2(Window::WIDTH * 0.25f, 20.0f), window.renderer, window.scoreFont, "0");
}

void World::update(const Input& input) {
    ball.update(*this);
    playerPaddle.update(*this, input);
    aiPaddle.update(*this, input);
}

void World::draw(const Window& window, const Input& input) const {
    // Set Screen to Black
    SDL_SetRenderDrawColor(window.renderer, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderClear(window.renderer);

    // Draw Dotted White Line
    SDL_SetRenderDrawColor(window.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    for (int y = 0; y < Window::HEIGHT; y++) { 
        if (y % 5) SDL_RenderDrawPoint(window.renderer, Window::WIDTH / 2, y); 
    }
    
    // Draw the objects
    ball.draw(window.renderer);
    playerPaddle.draw(window.renderer);
    aiPaddle.draw(window.renderer);
    for (auto& s : scores) { s.draw(); }
    if (input.pause) { pauseText.draw(); }

    // Swap buffers
    SDL_RenderPresent(window.renderer);
}