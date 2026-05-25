#ifndef NETWORK_H
#define NETWORK_H

#include "player.h"

int connectToServer();

void sendMessage(int socketFd,
                 const char* message);

void receiveMessages(int socketFd,
                     Player* player,
                     int* alienSpeed);

#endif