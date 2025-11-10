#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct Player {
    Rectangle rect;
    Vector2 position;
    Vector2 velocity;
    bool canJump;
    bool attacking;
    bool facing; // 0 para a direita e 1 para a esquerda
	Texture texture;
} Player;

#endif