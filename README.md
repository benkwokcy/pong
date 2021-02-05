# pong

Pong game written in two ways, using C++ and SDL.  

In the oop folder, I've written an object-oriented version, based off the tutorial from https://austinmorlan.com/posts/pong_clone/. The game objects (ball, paddle, score) modify each other directly by calling each other's functions.

In the functional folder, I've rewritten the game in a functional way, based off John Carmack's Quakecon 2013 keynote: https://youtu.be/1PhArSujR_A. Objects receive an immutable World state and instead of modifying each other, they pass events to an event queue. Then when we construct the next frame, we distribute these events to the object constructors. 

![Gameplay Demo](demo.png)

## Things I Learned From Writing This

- SDL (Window, Graphics, Audio, Font)
- Game Loop
- Object-oriented design in C++ (inheritance, virtual methods, RAII, ...)
- Functional design in C++ (std::function)

## Dependencies

- C++ 17  
- SDL2  
- SDL2_ttf 
- SDL2_mixer