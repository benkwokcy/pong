#pragma once

#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

// This takes care of creating and destroying the SDL window, renderer, and font.
class Window {
public:
    static constexpr int WINDOW_WIDTH = 640;
    static constexpr int WINDOW_HEIGHT = 480;
    static constexpr char GAME_NAME[] = "SHANSHAN";

    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* scoreFont;

    Window() {
        verify(SDL_Init(SDL_INIT_VIDEO), -1);
        verify(TTF_Init(), -1);
        verify(window = SDL_CreateWindow(GAME_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN), nullptr);        
        verify(renderer = SDL_CreateRenderer(window, -1, 0), nullptr);        
        verify(scoreFont = TTF_OpenFont("assets/DejaVuSans.ttf", 40), nullptr);
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
    void verify(const A actualCode, const B errorCode) const {
        if (actualCode == static_cast<A>(errorCode)) {
            cout << SDL_GetError() << endl;
            exit(EXIT_FAILURE);
        }
    }
};

// Used by the Input class
struct PaddleState {
    bool up = false;
    bool down = false;
};

// We maintain one of these objects and update it with input events every frame
struct Input {
    bool quit = false;
    PaddleState paddleStates[2];

    void update(const SDL_Event& event) {
        if (event.type == SDL_QUIT) { quit = true; } 

        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    quit = true; break;
                case SDLK_w:
                    paddleStates[0].up = true; break;
                case SDLK_s:
                    paddleStates[0].down = true; break;
                case SDLK_UP:
                    paddleStates[1].up = true; break;
                case SDLK_DOWN:
                    paddleStates[1].down = true; break;
            }
        } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_w:
                    paddleStates[0].up = false; break;
                case SDLK_s:
                    paddleStates[0].down = false; break;
                case SDLK_UP:
                    paddleStates[1].up = false; break;
                case SDLK_DOWN:
                    paddleStates[1].down = false; break;
            }
        }
    }
};

// Allows convenient arithmetic operations on a pair of floats.
struct Vec2 {
    Vec2(): x(0.0f), y(0.0f) {}
    Vec2(float x, float y): x(x), y(y) {}

    Vec2 operator+(const Vec2& other) const { 
        return Vec2(x + other.x, y + other.y); 
    }
    
    Vec2& operator+=(const Vec2& other) { 
        x += other.x;
        y += other.y;
        return *this; 
    }

    Vec2 operator*(const float scale) const { 
        return Vec2(x * scale, y * scale); 
    }

    float x, y;
};

// Abstract base class for all drawable objects.
struct Object {
    Object(Vec2 position) : position(position) {
        rect.x = static_cast<int>(position.x);
        rect.y = static_cast<int>(position.y);
    }
    virtual ~Object() = default;
    virtual void draw(SDL_Renderer* renderer) = 0;

    Vec2 position;
    SDL_Rect rect {};    
};

// Abstract base class for moving objects.
struct MovingObject : public Object {
    MovingObject(Vec2 position, Vec2 velocity) : Object(position), velocity(velocity) {}
    virtual ~MovingObject() = default;

    Vec2 velocity;
};

struct Ball : public Object {
    Ball(Vec2 position) : Object(position) {
        rect.w = WIDTH;
        rect.h = HEIGHT;
    }

    ~Ball() = default;

    void draw(SDL_Renderer* renderer) {
        rect.x = static_cast<int>(position.x);
        rect.y = static_cast<int>(position.y);
        SDL_RenderFillRect(renderer, &rect);
    }

    constexpr static int WIDTH = 15;
    constexpr static int HEIGHT = 15;
};

struct Paddle : public MovingObject {
    Paddle(Vec2 position, Vec2 velocity) : MovingObject(position, velocity) {
        rect.w = WIDTH;
        rect.h = HEIGHT;
    }
    ~Paddle() = default;

    void update(const PaddleState& paddleState) {
        if (paddleState.up) {
            velocity.y = -SPEED;
        } else if (paddleState.down) {
            velocity.y = SPEED;
        } else {
            velocity.y = 0.0f;
        }
        position.y += velocity.y;
        position.y = std::clamp(position.y, 0.0f, static_cast<float>(Window::WINDOW_HEIGHT - HEIGHT));
    }

    void draw(SDL_Renderer* renderer) {
        rect.y = static_cast<int>(position.y);
        SDL_RenderFillRect(renderer, &rect);
    }

    constexpr static float SPEED = 7.0f;
    constexpr static int WIDTH = 15;
    constexpr static int HEIGHT = 75;
};

struct Score : public Object {
    Score(Vec2 position, SDL_Renderer* renderer, TTF_Font* font) : Object(position), font(font) { 
        surface = TTF_RenderText_Solid(font, "0", {0xFF, 0xFF, 0xFF, 0xFF});
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        int width, height; 
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
        rect.w = width;
        rect.h = height;
    }

    ~Score() {
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    Score(const Score& other) = delete;
    Score& operator=(const Score& other) = delete;

    Score(Score&& other) :
        Object(std::move(other.position)),
        font(other.font)
    {
        rect = std::move(other.rect);
        surface = other.surface; other.surface = nullptr;
        texture = other.texture; other.texture = nullptr;
        other.font = nullptr;
    }

    Score& operator=(Score&& other) {
        position = std::move(other.position);
        rect = std::move(other.rect);
        font = other.font; other.font = nullptr;
        surface = other.surface; other.surface = nullptr;
        texture = other.texture; other.texture = nullptr;
        return *this;
    }

    void draw(SDL_Renderer* renderer) {
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }

    TTF_Font* font {};
    SDL_Surface* surface {};
    SDL_Texture* texture {};
};

// Manages the creation and drawing of all objects in the game.
struct Objects {
    Ball ball;
    vector<Paddle> paddles;
    vector<Score> scores;

    Objects(const Window& window) :
        ball(Vec2(Window::WINDOW_WIDTH / 2.0f - Ball::WIDTH / 2.0f, Window::WINDOW_HEIGHT / 2.0f - Ball::HEIGHT / 2.0f))
    {
        paddles.emplace_back(Vec2(50.0f, Window::WINDOW_HEIGHT / 2.0f - Paddle::HEIGHT / 2.0f), Vec2(0.0f, 0.0f));
        paddles.emplace_back(Vec2(Window::WINDOW_WIDTH - 50.0f, Window::WINDOW_HEIGHT / 2.0f - Paddle::HEIGHT / 2.0f), Vec2(0.0f, 0.0f));
        scores.emplace_back(Vec2(Window::WINDOW_WIDTH * 0.75f, 20.0f), window.renderer, window.scoreFont);
        scores.emplace_back(Vec2(Window::WINDOW_WIDTH * 0.25f, 20.0f), window.renderer, window.scoreFont);
    }

    void update(Input& input) {
        for (int i = 0; i < static_cast<int>(paddles.size()); i++) {
            paddles[i].update(input.paddleStates[i]);
        }
    }

    void draw(const Window& window) {
         // Set Screen to Black
        SDL_SetRenderDrawColor(window.renderer, 0x0, 0x0, 0x0, 0xFF);
        SDL_RenderClear(window.renderer);

        // Draw Dotted White Line
        SDL_SetRenderDrawColor(window.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        for (int y = 0; y < Window::WINDOW_HEIGHT; y++) { if (y % 5) SDL_RenderDrawPoint(window.renderer, Window::WINDOW_WIDTH / 2, y); }
        
        ball.draw(window.renderer);
        for (auto& p : paddles) { p.draw(window.renderer); }
        for (auto& s : scores) { s.draw(window.renderer); }

        SDL_RenderPresent(window.renderer);
    }
};