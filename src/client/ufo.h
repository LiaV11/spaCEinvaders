#ifndef UFO_H
#define UFO_H

typedef struct {

    int x;
    int y;
    int width;
    int height;
    int active;
    int direction;
    int points;

} UFO;

void initUFO(UFO* ufo);

#endif