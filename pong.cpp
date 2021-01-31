#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

SDL_Renderer* renderer;
SDL_Window* window;
TTF_Font* font;
SDL_Color color;
bool running;
int frameCount, timerFPS, lastFrame, fps;

constexpr int WIDTH = 720;
constexpr int HEIGHT = 720;

int main() {
    // if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
    //     cout << "Failed at SDL_Init" << endl;
    // if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0) 
    //     cout << "Failed at SDL_CreateWindowAndRenderer" << endl;
    return 0;
}