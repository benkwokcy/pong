#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL_mixer.h>

struct Audio {
    Mix_Chunk* wallHit;
    Mix_Chunk* paddleHit;

    Audio() {
        wallHit = Mix_LoadWAV("source/assets/wallHit.wav");
        paddleHit = Mix_LoadWAV("source/assets/paddleHit.wav");
    }

    void playWallHit() {
        Mix_PlayChannel(-1, wallHit, 0);
    }

    void playPaddleHit() {
        Mix_PlayChannel(-1, paddleHit, 0);
    }
};

#endif