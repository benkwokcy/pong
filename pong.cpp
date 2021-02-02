#include <iostream>
#include <chrono>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "pong.hpp"

using namespace std;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argcs[]) {
    Window window;
    Objects objects(window);
    Input input;
    
    while (!input.quit){       
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            input.update(event);
        }
        objects.update(input);
        objects.draw(window);
    }
   
    return 0;
}