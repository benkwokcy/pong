#pragma once

#include <vector>

#include "Audio.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "Score.hpp"
#include "Window.hpp"

using namespace std;

// Manager class for all stateful objects
struct World {
    Audio audio;
    Ball ball;
    vector<Paddle> paddles;
    vector<Score> scores;

    World(const Window& window);
    
    void update(const Input& input);
    void draw(const Window& window) const;
};