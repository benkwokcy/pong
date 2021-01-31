#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

constexpr int WINDOW_WIDTH = 640;
constexpr int WINDOW_HEIGHT = 480;

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Failed at SDL_Init" << endl;
        return 1;
    }
    
    SDL_Window* window = SDL_CreateWindow("Hello Shanshan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        cout << "Window could not be created" << endl;
        return 1;
    } 
    
    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);

    SDL_Event e;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN){
                quit = true;
            }
        }
    }
   
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}