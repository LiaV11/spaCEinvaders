#include "hud.h"

#include <SDL_ttf.h>
#include <stdio.h>

TTF_Font* font = NULL;

void renderHUD(SDL_Renderer* renderer,
               int score,
               int lives) {

    /*
    LOAD FONT
    */

    if (font == NULL) {

        font = TTF_OpenFont(
            "assets/font.ttf",
            22);

        if (!font) {

            printf("FONT ERROR: %s\n",
                   TTF_GetError());

            return;
        }

        printf("FONT LOADED\n");
    }

    /*
    TEXT
    */

    SDL_Color white = {

        255,
        255,
        255,
        255
    };

    char text[200];

    sprintf(text,
            "SCORE: %d   LIVES: %d",
            score,
            lives);

    SDL_Surface* textSurface =
        TTF_RenderText_Blended(
            font,
            text,
            white);

    if (!textSurface) {

        printf("TEXT SURFACE ERROR: %s\n",
               TTF_GetError());

        return;
    }

    SDL_Texture* textTexture =
        SDL_CreateTextureFromSurface(
            renderer,
            textSurface);

    SDL_Rect textRect = {

        15,
        10,

        textSurface->w,
        textSurface->h
    };

    SDL_RenderCopy(renderer,
                   textTexture,
                   NULL,
                   &textRect);

    SDL_FreeSurface(textSurface);

    SDL_DestroyTexture(textTexture);
}