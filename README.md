# pong

Pong game using C++ and SDL. Based off the tutorial from https://austinmorlan.com/posts/pong_clone/.

![Gameplay Demo](demo.png)

## Features Done

- Basic functionality (rendering, input, collision-detection)
- Fixed timestep game loop
- Score counters
- Sound effects
- Pause button
- AI Opponent

## Features To Do

- Clean up AI code -> controller class?
- Parent class for game objects -> position, velocity, getters and setters, reset
- Add sprites
- Add instructions at the bottom
- Add start menu
- Separate the collision detection from the objects
- Let collision account for side hits vs top hits vs corner hits

## Dependencies

- C++ 17  
- SDL2  
- SDL2_ttf 
- SDL2_mixer