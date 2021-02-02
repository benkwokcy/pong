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
        auto startTime = chrono::steady_clock::now(); 

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            input.update(event);
        }
        objects.update(input);
        objects.draw(window);

        auto endTime = chrono::steady_clock::now();
        auto timeToWait = 16.0f + chrono::duration<float, milli>(startTime - endTime).count();
        if (timeToWait > 0.0) { 
            SDL_Delay(static_cast<unsigned int>(timeToWait)); 
        } 
    }
   
    return 0;
}