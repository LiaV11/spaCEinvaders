#ifndef RENDER_H
#define RENDER_H

#include <SDL.h>

#include "player.h"
#include "bullet.h"
#include "enemy_bullet.h"
#include "alien.h"
#include "bunker.h"
#include "ufo.h"

void renderGame(
    SDL_Renderer* renderer,
    Player* player,
    Bullet* bullet,
    EnemyBullet enemyBullets[],
    Alien aliens[],
    int alienCount,
    Bunker bunkers[],
    UFO* ufo);

#endif