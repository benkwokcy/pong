#pragma once

#include "Ball.hpp"
#include "Paddle.hpp"
#include "Score.hpp"
#include "Window.hpp"
#include "Input.hpp"
#include <vector>

using namespace std;

// Manager class for all stateful objects
struct World {
    Input input;
    Ball ball;
    vector<Paddle> paddles;
    vector<Score> scores;

    World(const Window& window);
    void update();
    void draw(const Window& window) const;
};