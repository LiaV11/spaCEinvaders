#ifndef ENEMY_BULLET_H
#define ENEMY_BULLET_H

typedef struct {

    int x;
    int y;

    int active;

} EnemyBullet;

void shootEnemyBullet(
    EnemyBullet* bullet,
    int x,
    int y);

void updateEnemyBullet(
    EnemyBullet* bullet);

#endif