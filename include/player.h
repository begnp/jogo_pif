#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "map.h"

typedef struct Enemy Enemy;

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
    bool active;
    Texture currentTexture;
    Texture2D runTextures[4];
    Texture2D attackTextures[3]; 
    int currentFrame;
    float frameTimer;
    float frameSpeed;
    Texture2D idleTexture;
    Texture2D attackTexture;
} Player;

Player InitPlayer(Player *player, Texture initTex);

void IsPlayerAlive(Player *player);

bool CanAttack(Player *player, float time);

void StartPlayerAttack(Player *player, Enemy *enemy, Map *map);

bool CanConcludeAttack(Player *player, float time);

void ConcludePlayerAttack(Player *player);

#endif