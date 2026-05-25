#ifndef ALIEN_H
#define ALIEN_H

typedef struct {

    int x;
    int y;

    int width;
    int height;

    int alive;

    int exploding;
    int explosionTimer;

    int type;

} Alien;

void initAliens(Alien aliens[],
                int count);

#endif