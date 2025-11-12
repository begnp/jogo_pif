#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"

typedef struct Enemy {
    int id_enemy;
    Rectangle rect;
    Vector2 position;
    Vector2 velocity;
    Rectangle vision;
    bool attacking;
    bool facing; // 0 para a direita e 1 para a esquerda
    int health;
	Texture texture;
} Enemy;

Enemy InitEnemy(Enemy *enemy, Texture2D initTex, int idEnemy);

#endif