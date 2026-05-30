#include "audio.h"

#include <SDL_mixer.h>

Mix_Chunk* shootSound;
Mix_Chunk* explosionSound;

void initAudio() {

    Mix_OpenAudio(
        44100,
        MIX_DEFAULT_FORMAT,
        2,
        2048);

    shootSound =
        Mix_LoadWAV(
            "assets/shoot.mp3");

    explosionSound =
        Mix_LoadWAV(
            "assets/explosion.mp3");
}

void playShootSound() {

    Mix_PlayChannel(
        -1,
        shootSound,
        0);
}

void playExplosionSound() {

    Mix_PlayChannel(
        -1,
        explosionSound,
        0);
}

void closeAudio() {

    Mix_CloseAudio();
}