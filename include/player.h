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
    Rectangle hitbox;
    bool facing; // 0 para a direita e 1 para a esquerda
    int hearts;
	Texture texture;
} Player;

Player InitPlayer(Player *player, Texture initTex);

void IsplayerAttack(Player *player, Enemy *enemy);

#endif