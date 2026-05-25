#ifndef PLAYER_H
#define PLAYER_H

typedef struct {

    int x;
    int y;

    int width;
    int height;

    int lives;

    int score;

} Player;

void initPlayer(Player* player);

#endif