#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

constexpr int WINDOW_WIDTH = 640;
constexpr int WINDOW_HEIGHT = 480;
constexpr int BALL_WIDTH = 15;
constexpr int BALL_HEIGHT = 15;

void crash() {
    cout << SDL_GetError() << endl;
    exit(EXIT_FAILURE);
}

// Pair of floats that do memberwise addition and multiplication
struct Vec2 {
    Vec2(): x(0.0f), y(0.0f) {}
    Vec2(float x, float y): x(x), y(y) {}
    Vec2 operator+(Vec2 const& other) { return Vec2(x + other.x, y + other.y); }
    Vec2 operator*(const float scale) { return Vec2(x * scale, y * scale); }
    float x, y;
};

struct Ball {
    Ball(Vec2 position) : position(position) {
        rect.x = static_cast<int>(position.x);
        rect.y = static_cast<int>(position.y);
        rect.w = BALL_WIDTH;
        rect.h = BALL_HEIGHT;
    }
    void Draw(SDL_Renderer* renderer) {
        rect.x = static_cast<int>(position.x);
        rect.y = static_cast<int>(position.y);
        SDL_RenderFillRect(renderer, &rect);
    }

    Vec2 position;
    SDL_Rect rect {};
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argcs[]) {
    // Initialize the SDL library
    if (SDL_Init(SDL_INIT_VIDEO) < 0) { crash(); }
     
    // SDL_Window - a struct that contains the window info. Basically, the physical pixels on the screen.
    SDL_Window* window = SDL_CreateWindow("Hello Shanshan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) { crash(); }
    
    // SDL_Renderer - a struct that contains the rendering info. Render images inside our SDL_Window
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) { crash(); }

    // Create the ball
    Ball ball(Vec2(WINDOW_WIDTH / 2.0f - BALL_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f - BALL_HEIGHT / 2.0f));

    // Event loop
    bool quit = false;
    while (!quit){
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) { quit = true; } 
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) { quit = true; }

            // Set the screen to black
            SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
            SDL_RenderClear(renderer);

            // Draw dotted white line down the middle of the screen
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            for (int y = 0; y < WINDOW_HEIGHT; y++) {
                if (y % 5) SDL_RenderDrawPoint(renderer, WINDOW_WIDTH / 2, y);
            }

            ball.Draw(renderer);

            // Switch buffers
            SDL_RenderPresent(renderer);
        }
    }
   
    // Clean up and exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}