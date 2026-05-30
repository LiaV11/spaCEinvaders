#include "render.h"
#include "texture_manager.h"
#include "hud.h"
#include "constants.h"

void drawStars(SDL_Renderer* renderer) {

    SDL_SetRenderDrawColor(
        renderer,
        255,255,255,255);

    for (int i = 0; i < 120; i++) {

        int x = (i * 73) % 900;
        int y = (i * 97) % 700;

        SDL_RenderDrawPoint(renderer, x, y);
    }
}

void renderGame(
    SDL_Renderer* renderer,
    Player* player,
    Bullet* bullet,
    EnemyBullet enemyBullets[],
    Alien aliens[],
    int alienCount,
    Bunker bunkers[],
    UFO* ufo) {

    SDL_SetRenderDrawColor(
        renderer,
        5,5,25,255);

    SDL_RenderClear(renderer);

    drawStars(renderer);

    SDL_Rect floor = {
        0,
        660,
        900,
        40
    };

    SDL_SetRenderDrawColor(
        renderer,
        25,25,25,255);

    SDL_RenderFillRect(
        renderer,
        &floor);

    SDL_Rect playerRect = {

        player->x,
        player->y,

        player->width,
        player->height
    };

    SDL_RenderCopy(
        renderer,
        playerTexture,
        NULL,
        &playerRect
    );

    if (bullet->active) {

        SDL_SetRenderDrawColor(
            renderer,
            255,255,0,255);

        SDL_Rect bulletRect = {

            bullet->x,
            bullet->y,

            8,
            20
        };

        SDL_RenderFillRect(
            renderer,
            &bulletRect);
    }

    for (int i = 0;
        i < MAX_ENEMY_BULLETS;
        i++) {

        if (enemyBullets[i].active) {

            SDL_SetRenderDrawColor(
                renderer,
                255,0,0,255);

            SDL_Rect enemyBulletRect = {

                enemyBullets[i].x,
                enemyBullets[i].y,

                8,
                20
            };

            SDL_RenderFillRect(
                renderer,
                &enemyBulletRect);
        }
    }

    for (int i = 0;
        i < 4;
        i++) {

        if (bunkers[i].health <= 0) {
            continue;
        }

        int alpha = 255;

        if (bunkers[i].health <= 75) {
            alpha = 200;
        }

        if (bunkers[i].health <= 50) {
            alpha = 140;
        }

        if (bunkers[i].health <= 25) {
            alpha = 80;
        }

        SDL_SetTextureAlphaMod(
            bunkerTexture,
            alpha
        );

        SDL_Rect bunkerRect = {

            bunkers[i].x,
            bunkers[i].y,

            bunkers[i].width,
            bunkers[i].height
        };

        SDL_RenderCopy(
            renderer,
            bunkerTexture,
            NULL,
            &bunkerRect
        );
    }

    SDL_SetTextureAlphaMod(
        bunkerTexture,
        255
    );

    for (int i = 0;
         i < alienCount;
         i++) {

        if (!aliens[i].alive) {
            continue;
        }

        SDL_Rect alienRect = {

            aliens[i].x,
            aliens[i].y,

            aliens[i].width,
            aliens[i].height
        };

        if (aliens[i].type == 0) {

            SDL_RenderCopy(
                renderer,
                alienTexture1,
                NULL,
                &alienRect);
        }

        else if (aliens[i].type == 1) {

            SDL_RenderCopy(
                renderer,
                alienTexture2,
                NULL,
                &alienRect);
        }

        else {

            SDL_RenderCopy(
                renderer,
                alienTexture3,
                NULL,
                &alienRect);
        }
    }

    if (ufo->active) {

        SDL_Rect ufoRect = {

            ufo->x,
            ufo->y,

            ufo->width,
            ufo->height
        };

        SDL_RenderCopy(
            renderer,
            ufoTexture,
            NULL,
            &ufoRect);
    }

    renderHUD(
        renderer,
        player->score,
        player->lives);

    SDL_RenderPresent(renderer);
}