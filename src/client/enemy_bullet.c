#include "enemy_bullet.h"

void shootEnemyBullet(
    EnemyBullet* bullet,
    int x,
    int y) {

    if (!bullet->active) {

        bullet->x = x;
        bullet->y = y;

        bullet->active = 1;
    }
}

void updateEnemyBullet(
    EnemyBullet* bullet) {

    if (bullet->active) {

        bullet->y += 7;

        if (bullet->y > 700) {

            bullet->active = 0;
        }
    }
}