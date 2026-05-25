#include "bunker.h"

void initBunkers(Bunker bunkers[]) {

    int x = 100;

    for (int i = 0; i < 4; i++) {

        bunkers[i].x = x;

        bunkers[i].y = 500;

        bunkers[i].width = 110;

        bunkers[i].height = 60;

        bunkers[i].health = 100;

        x += 180;
    }
}