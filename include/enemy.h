#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"

typedef struct Player Player;

typedef struct Enemy {
    int id_enemy;
    Rectangle rect;
    Vector2 position;
    Vector2 velocity;
    Rectangle vision;
    bool attacking;
    bool targetInRange;
    float delayAttack;
    float attackTime;
	float lastAttack;
    Rectangle hitbox;
    bool facing; // 0 para a direita e 1 para a esquerda
    int health;
    bool active;
	Texture texture;
} Enemy;

Enemy InitEnemy(Enemy *enemy, Texture2D initTex, int idEnemy);

void IsEnemyAlive(Enemy *enemy);

void EnemyVision(Enemy *enemy, Player *player);

bool CanEnemyAttack(Enemy *enemy, Player *player, float time);

void DelayEnemyAttack(Enemy *enemy, Player *player, float time);

void StartEnemyAttack(Enemy *enemy, Player *player);

bool CanEnemyConcludeAttack(Enemy *enemy, float time);

void ConcludeEnemyAttack(Enemy *enemy);

#endif