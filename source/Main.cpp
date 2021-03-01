#include <iostream>
#include <chrono>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Window.hpp"
#include "World.hpp"
#include "Input.hpp"

using namespace std;

// Wait until at least 16ms have passed, capping the frame rate at 60FPS.
void wait(const chrono::time_point<chrono::steady_clock>& startTime) {
    const auto endTime = chrono::steady_clock::now();
    const auto timeElapsed = chrono::duration<float, milli>(endTime - startTime).count();
    const auto timeToWait = 16.0f - timeElapsed;
    if (timeToWait > 0.0) { SDL_Delay(static_cast<unsigned int>(timeToWait)); } 
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argcs[]) {
    const Window window;
    World world(window);
    Input input {};

    while (!input.quit){      
        const auto startTime = chrono::steady_clock::now();
        input.update();
        if (!input.pause) {
            world.update(input);
        }       
        world.draw(window, input);
        wait(startTime);
    }
   
    return 0;
}