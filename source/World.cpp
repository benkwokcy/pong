#include "Window.hpp"
#include "World.hpp"
#include "Ball.hpp"
#include "Score.hpp"
#include "Paddle.hpp"
#include "Input.hpp"
#include <vector>

using namespace std;

World::World(const Window& window) : 
    ball(Vec2(Window::WIDTH / 2.0f - Ball::WIDTH / 2.0f, Window::HEIGHT / 2.0f - Ball::HEIGHT / 2.0f), Vec2(Ball::HORIZONTAL_SPEED, 0.0f)) 
    {
        paddles.emplace_back(Vec2(50.0f, Window::HEIGHT / 2.0f - Paddle::HEIGHT / 2.0f), Vec2(0.0f, 0.0f));
        paddles.emplace_back(Vec2(Window::WIDTH - 50.0f, Window::HEIGHT / 2.0f - Paddle::HEIGHT / 2.0f), Vec2(0.0f, 0.0f));
        scores.emplace_back(Vec2(Window::WIDTH * 0.75f, 20.0f), window.renderer, window.scoreFont);
        scores.emplace_back(Vec2(Window::WIDTH * 0.25f, 20.0f), window.renderer, window.scoreFont);
    }

void World::update(const Input& input) {
    ball.update(*this);
    for (size_t i = 0; i < paddles.size(); i++) { paddles[i].update(input.paddleStates[i]); }
}

void World::draw(const Window& window) const {
    // Set Screen to Black
    SDL_SetRenderDrawColor(window.renderer, 0x0, 0x0, 0x0, 0xFF);
    SDL_RenderClear(window.renderer);

    // Draw Dotted White Line
    SDL_SetRenderDrawColor(window.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    for (int y = 0; y < Window::HEIGHT; y++) { if (y % 5) SDL_RenderDrawPoint(window.renderer, Window::WIDTH / 2, y); }
    
    // Draw the objects
    ball.draw(window.renderer);
    for (auto& p : paddles) { p.draw(window.renderer); }
    for (auto& s : scores) { s.draw(); }

    // Swap buffers
    SDL_RenderPresent(window.renderer);
}