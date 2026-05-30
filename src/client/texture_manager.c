#include "texture_manager.h"

#include <SDL_image.h>
#include <stdio.h>

/*
GLOBAL TEXTURES
*/

SDL_Texture* playerTexture;

SDL_Texture* alienTexture1;
SDL_Texture* alienTexture2;
SDL_Texture* alienTexture3;

SDL_Texture* explosionTexture;

SDL_Texture* bunkerTexture;

SDL_Texture* ufoTexture;

/*
LOAD TEXTURES
*/

void loadTextures(SDL_Renderer* renderer) {

    /*
    PLAYER
    */

    SDL_Surface* playerSurface =
        IMG_Load("assets/player.png");

    if (!playerSurface) {

        printf("ERROR player.png: %s\n",
               IMG_GetError());
    }

    playerTexture =
        SDL_CreateTextureFromSurface(
            renderer,
            playerSurface);

    SDL_FreeSurface(playerSurface);

    /*
    ALIEN 1
    */

    SDL_Surface* alien1Surface =
        IMG_Load("assets/alien1.png");

    if (!alien1Surface) {

        printf("ERROR alien1.png: %s\n",
               IMG_GetError());
    }

    alienTexture1 =
        SDL_CreateTextureFromSurface(
            renderer,
            alien1Surface);

    SDL_FreeSurface(alien1Surface);

    /*
    ALIEN 2
    */

    SDL_Surface* alien2Surface =
        IMG_Load("assets/alien2.png");

    if (!alien2Surface) {

        printf("ERROR alien2.png: %s\n",
               IMG_GetError());
    }

    alienTexture2 =
        SDL_CreateTextureFromSurface(
            renderer,
            alien2Surface);

    SDL_FreeSurface(alien2Surface);

    /*
    ALIEN 3
    */

    SDL_Surface* alien3Surface =
        IMG_Load("assets/alien3.png");

    if (!alien3Surface) {

        printf("ERROR alien3.png: %s\n",
               IMG_GetError());
    }

    alienTexture3 =
        SDL_CreateTextureFromSurface(
            renderer,
            alien3Surface);

    SDL_FreeSurface(alien3Surface);

    /*
    EXPLOSION
    */

    SDL_Surface* explosionSurface =
        IMG_Load("assets/explosion.png");

    if (!explosionSurface) {

        printf("ERROR explosion.png: %s\n",
               IMG_GetError());
    }

    explosionTexture =
        SDL_CreateTextureFromSurface(
            renderer,
            explosionSurface);

    SDL_FreeSurface(explosionSurface);

    /*
    BUNKER
    */

    SDL_Surface* bunkerSurface =
        IMG_Load("assets/bunker.png");

    if (!bunkerSurface) {

        printf("ERROR bunker.png: %s\n",
               IMG_GetError());
    }

    bunkerTexture =
        SDL_CreateTextureFromSurface(
            renderer,
            bunkerSurface);

    SDL_FreeSurface(bunkerSurface);

    /*
    UFO
    */

    SDL_Surface* ufoSurface =
        IMG_Load("assets/ufo.png");

    if (!ufoSurface) {

        printf("ERROR ufo.png: %s\n",
               IMG_GetError());
    }

    ufoTexture =
        SDL_CreateTextureFromSurface(
            renderer,
            ufoSurface);

    SDL_FreeSurface(ufoSurface);
}

void destroyTextures() {

    SDL_DestroyTexture(playerTexture);

    SDL_DestroyTexture(alienTexture1);
    SDL_DestroyTexture(alienTexture2);
    SDL_DestroyTexture(alienTexture3);

    SDL_DestroyTexture(explosionTexture);

    SDL_DestroyTexture(bunkerTexture);

    SDL_DestroyTexture(ufoTexture);
}