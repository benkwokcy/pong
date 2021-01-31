#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

constexpr int WIDTH = 640;
constexpr int HEIGHT = 480;

int main() {
    SDL_Window* window = nullptr;
    SDL_Surface* screenSurface = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Failed at SDL_Init" << endl;
    } else {
        window = SDL_CreateWindow("Hello Shanshan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if (!window) {
            cout << "Window could not be created" << endl;
        } else {
            screenSurface = SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
            SDL_UpdateWindowSurface(window);
            SDL_Delay(2000);
        }
    }
   
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}