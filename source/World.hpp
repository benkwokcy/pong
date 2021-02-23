#pragma once

#include <vector>

#include "Audio.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "Score.hpp"

using namespace std;

class Window;

// Manager class for all stateful objects
struct World {
    Audio audio;
    Ball ball;
    Paddle playerPaddle;
    Paddle aiPaddle;
    vector<Score> scores;

    World(const Window& window);
    
    void update(const Input& input);
    void draw(const Window& window) const;
};