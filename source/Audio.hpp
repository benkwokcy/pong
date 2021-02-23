#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL_mixer.h>

class Audio {
public:
    Audio() {
        wallHit = Mix_LoadWAV("source/assets/wallHit.wav");
        paddleHit = Mix_LoadWAV("source/assets/paddleHit.wav");
    }

    void playWallHit() const {
        Mix_PlayChannel(-1, wallHit, 0);
    }

    void playPaddleHit() const {
        Mix_PlayChannel(-1, paddleHit, 0);
    }
private:
    Mix_Chunk* wallHit;
    Mix_Chunk* paddleHit;
};

#endif