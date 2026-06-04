#ifndef NETWORK_H
#define NETWORK_H

#include "player.h"
#include "ufo.h"
#include "alien.h"
#include "bullet.h"
#include "enemy_bullet.h"
#include "bunker.h"

int connectToServer();

void sendMessage(
    int socketFd,
    const char* message
);

void receiveMessages(
    int socketFd,
    Player* player,
    int* alienSpeed,
    UFO* ufo,
    Alien aliens[]
);

void receiveMessagesSpectator(
    int socketFd,
    Player* player,
    int* alienSpeed,
    UFO* ufo,
    Alien aliens[],
    Bullet* bullet,
    EnemyBullet enemyBullets[],
    Bunker bunkers[]
);

#endif