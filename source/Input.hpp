#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

struct PaddleState {
    bool up = false;
    bool down = false;
};

// We maintain one of these objects and update it based on the user keyboard input every frame
struct Input {
    bool quit = false;
    bool pause = false;
    PaddleState paddleStates[2];

    void update() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) { 
                quit = true; 
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:   quit = true; break;
                    case SDLK_w:        paddleStates[0].up = true; break;
                    case SDLK_s:        paddleStates[0].down = true; break;
                    case SDLK_UP:       paddleStates[1].up = true; break;
                    case SDLK_DOWN:     paddleStates[1].down = true; break;
                    case SDLK_p:        pause = !pause; break;
                }
            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_w:        paddleStates[0].up = false; break;
                    case SDLK_s:        paddleStates[0].down = false; break;
                    case SDLK_UP:       paddleStates[1].up = false; break;
                    case SDLK_DOWN:     paddleStates[1].down = false; break;
                }
            }
        }
    }
};

#endif