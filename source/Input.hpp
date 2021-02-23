#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

// We maintain one of these objects and update it based on the user keyboard input every frame
struct Input {
    bool quit = false;
    bool pause = false;
    bool paddleUp = false;
    bool paddleDown = false;

    void update() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) { 
                quit = true; 
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:   quit = true; break;
                    case SDLK_w:        paddleUp = true; break;
                    case SDLK_s:        paddleDown = true; break;
                    // case SDLK_UP:       paddleUp = true; break;
                    // case SDLK_DOWN:     paddleDown = true; break;
                    case SDLK_p:        pause = !pause; break;
                }
            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_w:        paddleUp = false; break;
                    case SDLK_s:        paddleDown = false; break;
                    // case SDLK_UP:       paddleUp = false; break;
                    // case SDLK_DOWN:     paddleDown = false; break;
                }
            }
        }
    }
};

#endif