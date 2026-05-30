#include "game.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <winsock2.h>

#include "constants.h"
#include "player.h"
#include "bullet.h"
#include "alien.h"
#include "render.h"
#include "bunker.h"
#include "texture_manager.h"
#include "hud.h"
#include "audio.h"
#include "enemy_bullet.h"
#include "network.h"
#include "ufo.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int checkCollision(Bullet* bullet, Alien* alien) {

    if (!bullet->active || !alien->alive) {
        return 0;
    }

    return bullet->x < alien->x + alien->width &&
           bullet->x + 8 > alien->x &&
           bullet->y < alien->y + alien->height &&
           bullet->y + 20 > alien->y;
}

int bulletHitsBunker(Bullet* bullet, Bunker* bunker) {

    if (!bullet->active || bunker->health <= 0) {
        return 0;
    }

    return bullet->x < bunker->x + bunker->width &&
           bullet->x + 8 > bunker->x &&
           bullet->y < bunker->y + bunker->height &&
           bullet->y + 20 > bunker->y;
}

int checkUFOCollision(Bullet* bullet, UFO* ufo) {

    if (!bullet->active || !ufo->active) {
        return 0;
    }

    return bullet->x < ufo->x + ufo->width &&
           bullet->x + 8 > ufo->x &&
           bullet->y < ufo->y + ufo->height &&
           bullet->y + 20 > ufo->y;
}

void runGame() {

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    initAudio();

    SDL_Window* window =
        SDL_CreateWindow(
            "spaCEinvaders",
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

    int moveLeft = 0;
    int moveRight = 0;

    int alienDirection = 1;
    int alienSpeed = 2;

    int shootCooldown = 0;

    srand(time(NULL));

    while (running) {

        receiveMessages(
            socketFd,
            &player,
            &alienSpeed,
            &ufo,
            aliens
        );

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
                running = 0;
            }

            if (event.type == SDL_KEYDOWN) {

                if (event.key.keysym.sym == SDLK_LEFT) {
                    moveLeft = 1;
                }

                if (event.key.keysym.sym == SDLK_RIGHT) {
                    moveRight = 1;
                }

                if (event.key.keysym.sym == SDLK_SPACE) {

                    if (!bullet.active && shootCooldown == 0) {

                        shootBullet(
                            &bullet,
                            player.x + player.width / 2 - 4,
                            player.y - 20
                        );

                        shootCooldown = 15;

                        playShootSound();
                    }
                }
            }

            if (event.type == SDL_KEYUP) {

                if (event.key.keysym.sym == SDLK_LEFT) {
                    moveLeft = 0;
                }

                if (event.key.keysym.sym == SDLK_RIGHT) {
                    moveRight = 0;
                }
            }
        }

        if (shootCooldown > 0) {
            shootCooldown--;
        }

        if (moveLeft && player.x > 0) {
            player.x -= PLAYER_SPEED;
        }

        if (moveRight &&
            player.x + player.width < WINDOW_WIDTH) {

            player.x += PLAYER_SPEED;
        }

        updateBullet(&bullet);

        for (int i = 0; i < 4; i++) {

            if (bulletHitsBunker(&bullet, &bunkers[i])) {

                bullet.active = 0;

                bunkers[i].health -= 10;

                if (bunkers[i].health <= 0) {

                    bunkers[i].width = 0;
                    bunkers[i].height = 0;
                }
            }
        }

        for (int i = 0; i < MAX_ENEMY_BULLETS; i++) {
            updateEnemyBullet(&enemyBullets[i]);
        }

        /*
        ENEMY BULLETS VS BUNKERS
        */

        for (int i = 0; i < MAX_ENEMY_BULLETS; i++) {

            for (int j = 0; j < 4; j++) {

                if (

                    enemyBullets[i].active &&

                    enemyBullets[i].x <
                    bunkers[j].x +
                    bunkers[j].width &&

                    enemyBullets[i].x + 8 >
                    bunkers[j].x &&

                    enemyBullets[i].y <
                    bunkers[j].y +
                    bunkers[j].height &&

                    enemyBullets[i].y + 20 >
                    bunkers[j].y

                ) {

                    enemyBullets[i].active = 0;

                    bunkers[j].health -= 20;

                    if (bunkers[j].health <= 0) {

                        bunkers[j].width = 0;
                        bunkers[j].height = 0;
                    }
                }
            }
        }

        for (int i = 0; i < MAX_ENEMY_BULLETS; i++) {

            if (enemyBullets[i].active) {

                if (
                    enemyBullets[i].x < player.x + player.width &&
                    enemyBullets[i].x + 8 > player.x &&
                    enemyBullets[i].y < player.y + player.height &&
                    enemyBullets[i].y + 20 > player.y
                ) {

                    enemyBullets[i].active = 0;

                    player.lives--;

                    if (player.lives < 0) {
                        player.lives = 0;
                    }

                    playExplosionSound();

                    if (player.lives <= 0) {

                        SDL_ShowSimpleMessageBox(
                            SDL_MESSAGEBOX_ERROR,
                            "GAME OVER",
                            "Perdiste todas las vidas",
                            window
                        );

                        running = 0;
                    }
                }
            }
        }

        int moveDown = 0;

        for (int i = 0; i < MAX_ALIENS; i++) {

            if (aliens[i].alive) {

                aliens[i].x += alienDirection * alienSpeed;

                if (
                    aliens[i].x <= 20 ||
                    aliens[i].x + aliens[i].width >= WINDOW_WIDTH - 20
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

        for (int i = 0; i < MAX_ALIENS; i++) {

            if (checkCollision(&bullet, &aliens[i])) {

                bullet.active = 0;

                aliens[i].alive = 0;

                int points = 10;

                if (aliens[i].type == 0) {
                    points = 40;
                }
                else if (aliens[i].type == 1) {
                    points = 20;
                }

                player.score += points;

                playExplosionSound();
            }
        }

        for (int i = 0; i < MAX_ENEMY_BULLETS; i++) {

            if (!enemyBullets[i].active &&
                rand() % 1000 < 4) {

                int randomAlien =
                    rand() % MAX_ALIENS;

                if (aliens[randomAlien].alive) {

                    shootEnemyBullet(
                        &enemyBullets[i],
                        aliens[randomAlien].x +
                        aliens[randomAlien].width / 2,
                        aliens[randomAlien].y +
                        aliens[randomAlien].height
                    );
                }
            }
        }

        /*
        GAME OVER
        */

        for (int i = 0; i < MAX_ALIENS; i++) {

            if (aliens[i].alive &&
                aliens[i].y > 520) {

                SDL_ShowSimpleMessageBox(
                    SDL_MESSAGEBOX_ERROR,
                    "GAME OVER",
                    "Los aliens llegaron a la tierra",
                    window
                );

                running = 0;
            }
        }

        /*
        NEXT ROUND
        */

        int aliensAlive = 0;

        for (int i = 0; i < MAX_ALIENS; i++) {

            if (aliens[i].alive) {
                aliensAlive++;
            }
        }

        if (aliensAlive == 0) {

            alienSpeed++;

            initAliens(
                aliens,
                MAX_ALIENS
            );

            bullet.active = 0;
        }

        if (ufo.active) {
            ufo.x += 4 * ufo.direction;
        }

        if (checkUFOCollision(&bullet, &ufo)) {

            bullet.active = 0;

            player.score += ufo.points;

            ufo.active = 0;
        }

        /*
        RESET UFO
        */

        if (ufo.x > WINDOW_WIDTH + 150 ||
            ufo.x < -150) {

            ufo.active = 0;
        }

        /*
        RANDOM UFO SPAWN
        */

        if (!ufo.active &&
            rand() % 1800 == 1) {

            ufo.active = 1;

            ufo.direction = 1;

            ufo.x = -120;

            int randomValue = rand() % 3;

            if (randomValue == 0) {
                ufo.points = 100;
            }
            else if (randomValue == 1) {
                ufo.points = 200;
            }
            else {
                ufo.points = 500;
            }
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

        /*
        WIN
        */

        if (player.score >= 3500) {

            SDL_ShowSimpleMessageBox(
                SDL_MESSAGEBOX_INFORMATION,
                "YOU WIN",
                "Ganaste la partida",
                window
            );

            running = 0;
        }
    }

    closesocket(socketFd);

    WSACleanup();
    destroyTextures();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    closeAudio();

    SDL_Quit();
}