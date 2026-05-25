#ifndef BUNKER_H
#define BUNKER_H

typedef struct {

    int x;
    int y;

    int width;
    int height;

    int health;

} Bunker;

void initBunkers(Bunker bunkers[]);

#endif