#include "player.h"

void initPlayer(Player* player) {

    player->width = 100;
    player->height = 70;

    player->x = 400;

    player->y = 590;

    player->lives = 3;

    player->score = 0;
}