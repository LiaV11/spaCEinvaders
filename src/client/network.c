#include "network.h"
#include "constants.h"

#include <winsock2.h>

#include <stdio.h>
#include <string.h>

#pragma comment(lib, "ws2_32.lib")

int connectToServer() {

    WSADATA wsa;

    WSAStartup(MAKEWORD(2,2), &wsa);

    int clientSocket =
        socket(AF_INET,
               SOCK_STREAM,
               0);

    struct sockaddr_in server;

    server.sin_addr.s_addr =
        inet_addr(SERVER_IP);

    server.sin_family = AF_INET;

    server.sin_port =
        htons(SERVER_PORT);

    connect(clientSocket,
            (struct sockaddr*)&server,
            sizeof(server));

    printf("Conectado al servidor\n");

    return clientSocket;
}

void sendMessage(int socketFd,
                 const char* message) {

    char buffer[256];

    sprintf(buffer,
            "%s\n",
            message);

    send(socketFd,
         buffer,
         strlen(buffer),
         0);
}

void receiveMessages(int socketFd,
                     Player* player,
                     int* alienSpeed) {

    char buffer[256];

    int bytes =
        recv(socketFd,
             buffer,
             sizeof(buffer) - 1,
             0);

    if (bytes > 0) {

        buffer[bytes] = '\0';

        if (strncmp(buffer,
                    "UPDATE_SCORE",
                    12) == 0) {

            sscanf(buffer,
                   "UPDATE_SCORE %d",
                   &player->score);
        }

        else if (strncmp(buffer,
                         "UPDATE_LIVES",
                         13) == 0) {

            sscanf(buffer,
                   "UPDATE_LIVES %d",
                   &player->lives);
        }

        else if (strncmp(buffer,
                         "SPEED",
                         5) == 0) {

            sscanf(buffer,
                   "SPEED %d",
                   alienSpeed);
        }
    }
}