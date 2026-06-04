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
        socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server;

    server.sin_addr.s_addr =
        inet_addr(SERVER_IP);

    server.sin_family = AF_INET;

    server.sin_port =
        htons(SERVER_PORT);

    connect(
        clientSocket,
        (struct sockaddr*)&server,
        sizeof(server)
    );

    u_long mode = 1;

    ioctlsocket(
        clientSocket,
        FIONBIO,
        &mode
    );

    printf("Conectado al servidor\n");

    return clientSocket;
}

void sendMessage(
    int socketFd,
    const char* message
) {

    char buffer[256];

    sprintf(buffer, "%s\n", message);

    send(
        socketFd,
        buffer,
        strlen(buffer),
        0
    );
}

void receiveMessages(
    int socketFd,
    Player* player,
    int* alienSpeed,
    UFO* ufo,
    Alien aliens[]
) {

    char buffer[256];

    int bytes =
        recv(
            socketFd,
            buffer,
            sizeof(buffer) - 1,
            0
        );

    if (bytes <= 0) {
        return;
    }

    buffer[bytes] = '\0';

    char* line =
        strtok(buffer, "\n");

    while (line != NULL) {

        if (strncmp(line,
                    "UPDATE_SCORE",
                    12) == 0) {

            sscanf(
                line,
                "UPDATE_SCORE %d",
                &player->score
            );
        }

        else if (
            strncmp(
                line,
                "UPDATE_LIVES",
                13
            ) == 0
        ) {

            sscanf(
                line,
                "UPDATE_LIVES %d",
                &player->lives
            );
        }

        else if (
            strncmp(
                line,
                "SPEED",
                5
            ) == 0
        ) {

            sscanf(
                line,
                "SPEED %d",
                alienSpeed
            );
        }

        else if (
            strncmp(
                line,
                "ALIEN_DIED",
                11
            ) == 0
        ) {

            int alienId;

            sscanf(
                line,
                "ALIEN_DIED %d",
                &alienId
            );

            if (
                alienId >= 0 &&
                alienId < MAX_ALIENS
            ) {

                aliens[alienId].alive = 0;
            }
        }

        else if (
            strncmp(
                line,
                "CREATE_UFO",
                10
            ) == 0
        ) {

            char direction[32];

            int points;

            sscanf(
                line,
                "CREATE_UFO %s %d",
                direction,
                &points
            );

            ufo->active = 1;
            ufo->points = points;

            if (
                strcmp(
                    direction,
                    "LEFT_RIGHT"
                ) == 0
            ) {

                ufo->direction = 1;
                ufo->x = -120;
            }

            else {

                ufo->direction = -1;
                ufo->x = WINDOW_WIDTH + 120;
            }
        }

        line = strtok(NULL, "\n");
    }
}

void receiveMessagesSpectator(
    int socketFd,
    Player* player,
    int* alienSpeed,
    UFO* ufo,
    Alien aliens[],
    Bullet* bullet,
    EnemyBullet enemyBullets[],
    Bunker bunkers[]
) {

    char buffer[256];

    int bytes =
        recv(
            socketFd,
            buffer,
            sizeof(buffer) - 1,
            0
        );

    if (bytes <= 0) {
        return;
    }

    buffer[bytes] = '\0';

    char* line =
        strtok(buffer, "\n");

    while (line != NULL) {

        if (strncmp(line, "UPDATE_SCORE", 12) == 0) {

            sscanf(
                line,
                "UPDATE_SCORE %d",
                &player->score
            );
        }

        else if (strncmp(line, "UPDATE_LIVES", 12) == 0) {

            sscanf(
                line,
                "UPDATE_LIVES %d",
                &player->lives
            );
        }

        else if (strncmp(line, "SPEED", 5) == 0) {

            sscanf(
                line,
                "SPEED %d",
                alienSpeed
            );
        }

        else if (strncmp(line, "ALIEN_DIED", 10) == 0) {

            int alienId;

            sscanf(
                line,
                "ALIEN_DIED %d",
                &alienId
            );

            if (
                alienId >= 0 &&
                alienId < MAX_ALIENS
            ) {
                aliens[alienId].alive = 0;
            }
        }

        else if (strncmp(line, "CREATE_UFO", 10) == 0) {

            char direction[32];
            int points;

            sscanf(
                line,
                "CREATE_UFO %s %d",
                direction,
                &points
            );

            ufo->active = 1;
            ufo->points = points;

            if (strcmp(direction, "LEFT_RIGHT") == 0) {

                ufo->direction = 1;
                ufo->x = -120;
            }

            else {

                ufo->direction = -1;
                ufo->x = WINDOW_WIDTH + 120;
            }
        }

        else if (strncmp(line, "PLAYER_POS", 10) == 0) {

            sscanf(
                line,
                "PLAYER_POS %d %d",
                &player->x,
                &player->y
            );
        }

        else if (strncmp(line, "BULLET_PLAYER", 13) == 0) {

            sscanf(
                line,
                "BULLET_PLAYER %d %d %d",
                &bullet->x,
                &bullet->y,
                &bullet->active
            );
        }

        else if (strncmp(line, "BULLET_ENEMY", 12) == 0) {

            int idx;

            sscanf(
                line,
                "BULLET_ENEMY %d %d %d %d",
                &idx,
                &enemyBullets[idx].x,
                &enemyBullets[idx].y,
                &enemyBullets[idx].active
            );
        }

        else if (strncmp(line, "BULLET_BUNKER", 13) == 0) {

            int bunkerId;
            int health;

            sscanf(
                line,
                "BULLET_BUNKER %d %d",
                &bunkerId,
                &health
            );

            if (bunkerId >= 0 && bunkerId < 4) {
                bunkers[bunkerId].health = health;
            }
        }

        line = strtok(NULL, "\n");
    }
}