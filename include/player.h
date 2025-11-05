#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct Player {
    Rectangle rect;
    Vector2 velocity;
    bool canJump;
	Texture texture;
} Player;

#endif