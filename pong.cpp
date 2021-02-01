#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "objects.hpp"
#include "utilities.hpp"

using namespace std;

void crash() {
    cout << SDL_GetError() << endl;
    exit(EXIT_FAILURE);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argcs[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) { crash(); }
    if (TTF_Init() < 0) { crash(); }
     
    // Initialize Window
    SDL_Window* window = SDL_CreateWindow("PONG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) { crash(); }
    
    // Initialize Renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) { crash(); }

    // Initialize Font
    TTF_Font* scoreFont = TTF_OpenFont("assets/DejaVuSans.ttf", 40);

    // Create Objects
    Ball ball(Vec2(WINDOW_WIDTH / 2.0f - Ball::WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f - Ball::HEIGHT / 2.0f));
    Paddle paddleOne(
        Vec2(50.0f, WINDOW_HEIGHT / 2.0f - Paddle::HEIGHT / 2.0f),
        Vec2(0.0f, 0.0f)
    );
    Paddle paddleTwo(
        Vec2(WINDOW_WIDTH - 50.0f, WINDOW_HEIGHT / 2.0f - Paddle::HEIGHT / 2.0f),
        Vec2(0.0f, 0.0f)
    );
    Score scoreOne(Vec2(WINDOW_WIDTH / 4.0f, 20.0f), renderer, scoreFont);
    Score scoreTwo(Vec2(WINDOW_WIDTH * 0.75f, 20.0f), renderer, scoreFont);

    // Main Loop
    bool quit = false;
    while (!quit){
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // Read Input
            if (event.type == SDL_QUIT) { quit = true; } 
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) { quit = true; }

            // Set Screen to Black
            SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
            SDL_RenderClear(renderer);

            // Draw Dotted White Line
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            for (int y = 0; y < WINDOW_HEIGHT; y++) { 
                if (y % 5) SDL_RenderDrawPoint(renderer, WINDOW_WIDTH / 2, y);
            }

            // Draw Objects
            ball.draw(renderer);
            paddleOne.draw(renderer);
            paddleTwo.draw(renderer);
            scoreOne.draw(renderer);
            scoreTwo.draw(renderer);

            // Switch Buffers
            SDL_RenderPresent(renderer);
        }
    }
   
    // Clean Up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(scoreFont);
    TTF_Quit();
    SDL_Quit();

    return 0;
}