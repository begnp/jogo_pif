#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "enemy.h"

typedef struct Player {
    Rectangle rect;
    Vector2 position;
    Vector2 velocity;
    bool canJump;
    bool attacking;
    float attackTime;
	float lastAttack;
    Rectangle hitbox;
    bool facing; // 0 para a direita e 1 para a esquerda
    int hearts;
	Texture texture;
} Player;

Player InitPlayer(Player *player, Texture initTex);

bool CanAttack(Player *player, float time);

void StartPlayerAttack(Player *player, Enemy *enemy);

bool CanConcludeAttack(Player *player, float time);

void ConcludePlayerAttack(Player *player);

#endif