#ifndef HUD_H
#define HUD_H

#include <SDL.h>
#include <SDL_ttf.h>

void renderHUD(
    SDL_Renderer* renderer,
    int score,
    int lives);

#endif