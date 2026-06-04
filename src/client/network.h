#ifndef NETWORK_H
#define NETWORK_H

#include "player.h"
#include "ufo.h"
#include "alien.h"

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
    Alien aliens[]
);

#endif