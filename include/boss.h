#ifndef BOSS_H
#define BOSS_H

#include "raylib.h"

typedef struct Player Player;

typedef struct Boss {
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
} Boss;

Boss InitBoss(Boss *boss, Texture2D initTex);

void IsBossAlive(Boss *boss);

void BossVision(Boss *boss, Player *player);

bool CanBossAttack(Boss *boss, Player *player, float time);

void DelayBossAttack(Boss *boss, Player *player, float time);

void StartBossAttack(Boss *boss, Player *player);

bool CanBossConcludeAttack(Boss *boss, float time);

void ConcludeBossAttack(Boss *boss);

#endif