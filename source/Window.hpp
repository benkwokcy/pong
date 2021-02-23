#pragma once

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

using namespace std;

// This takes care of creating and destroying the SDL window, renderer, and font.
class Window {
public:
    static constexpr int WIDTH = 640;
    static constexpr int HEIGHT = 480;
    static constexpr char GAME_NAME[] = "PONNNNNNNNG!";

    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* scoreFont;

    Window() {
        verify(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO), -1);
        verify(TTF_Init(), -1);
        verify(window = SDL_CreateWindow(GAME_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN), nullptr);        
        verify(renderer = SDL_CreateRenderer(window, -1, 0), nullptr);        
        verify(scoreFont = TTF_OpenFont("source/assets/DejaVuSans.ttf", 40), nullptr);
        verify(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048), -1);
        Mix_Volume(-1, 8);
    }

    ~Window() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_CloseFont(scoreFont);
        TTF_Quit();
        SDL_Quit();
    }
private:
    // Crash if code is equal to error code
    template <typename A, typename B>
    void verify(const A actualCode, const B errorCode) {
        if (actualCode == static_cast<A>(errorCode)) {
            std::cout << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
    }
};
