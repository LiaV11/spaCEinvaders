#include "spectator_game.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <winsock2.h>

#include "../client/constants.h"
#include "../client/player.h"
#include "../client/bullet.h"
#include "../client/alien.h"
#include "../client/render.h"
#include "../client/bunker.h"
#include "../client/texture_manager.h"
#include "../client/hud.h"
#include "../client/audio.h"
#include "../client/enemy_bullet.h"
#include "../client/network.h"
#include "../client/ufo.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void runSpectator() {

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    initAudio();

    SDL_Window* window =
        SDL_CreateWindow(
            "spaCEinvaders - Espectador",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            0
        );

    SDL_Renderer* renderer =
        SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED
        );

    loadTextures(renderer);

    int socketFd = connectToServer();

    Player player;
    initPlayer(&player);

    Bullet bullet = {0};

    EnemyBullet enemyBullets[MAX_ENEMY_BULLETS] = {0};

    Alien aliens[MAX_ALIENS];
    initAliens(aliens, MAX_ALIENS);

    UFO ufo;
    initUFO(&ufo);

    Bunker bunkers[4];
    initBunkers(bunkers);

    int running = 1;
    SDL_Event event;

    int alienDirection = 1;
    int alienSpeed = 2;

    while (running) {

        receiveMessagesSpectator(
            socketFd,
            &player,
            &alienSpeed,
            &ufo,
            aliens,
            &bullet,
            enemyBullets,
            bunkers
        );

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        /*
        ALIEN MOVEMENT
        */

        int moveDown = 0;

        for (int i = 0; i < MAX_ALIENS; i++) {

            if (aliens[i].alive) {

                aliens[i].x +=
                    alienDirection * alienSpeed;

                if (
                    aliens[i].x <= 20 ||
                    aliens[i].x + aliens[i].width
                    >= WINDOW_WIDTH - 20
                ) {
                    moveDown = 1;
                }
            }
        }

        if (moveDown) {

            alienDirection *= -1;

            for (int i = 0; i < MAX_ALIENS; i++) {
                aliens[i].y += 15;
            }
        }

        /*
        NEXT ROUND DETECTION
        */

        int aliensAlive = 0;

        for (int i = 0; i < MAX_ALIENS; i++) {

            if (aliens[i].alive) {
                aliensAlive++;
            }
        }

        if (aliensAlive == 0) {

            alienSpeed++;

            initAliens(aliens, MAX_ALIENS);
        }

        /*
        UFO MOVEMENT
        */

        if (ufo.active) {
            ufo.x += 4 * ufo.direction;
        }

        if (
            ufo.x > WINDOW_WIDTH + 150 ||
            ufo.x < -150
        ) {
            ufo.active = 0;
        }

        renderGame(
            renderer,
            &player,
            &bullet,
            enemyBullets,
            aliens,
            MAX_ALIENS,
            bunkers,
            &ufo
        );

        SDL_Delay(16);
    }

    closesocket(socketFd);

    WSACleanup();
    destroyTextures();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    closeAudio();

    SDL_Quit();
}
