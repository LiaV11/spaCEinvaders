#include "bullet.h"
#include "constants.h"

void shootBullet(Bullet* bullet,
                 int x,
                 int y) {

    if (!bullet->active) {

        bullet->x = x;
        bullet->y = y;

        bullet->active = 1;
    }
}

void updateBullet(Bullet* bullet) {

    if (bullet->active) {

        bullet->y -= BULLET_SPEED;

        if (bullet->y < 0) {
            bullet->active = 0;
        }
    }
}