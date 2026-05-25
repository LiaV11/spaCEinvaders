#ifndef BULLET_H
#define BULLET_H

typedef struct {

    int x;
    int y;

    int active;

} Bullet;

void shootBullet(Bullet* bullet, int x, int y);

void updateBullet(Bullet* bullet);

#endif