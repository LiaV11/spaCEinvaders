#include "ufo.h"

void initUFO(UFO* ufo) {

    ufo->x = -120;

    ufo->y = 20;

    ufo->width = 100;

    ufo->height = 50;

    ufo->active = 1;

    ufo->direction = 1;
    
    ufo->points = 500;
}