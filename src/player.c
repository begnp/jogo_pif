#include "player.h"
#include "enemy.h"

#define KEY_ATTACK KEY_SPACE
#define TIME_ATTACK 0.5
#define COOLDOWN_ATTACK 0.2

Player InitPlayer(Player *player, Texture2D initTex) {
    player->texture = initTex; //textura inicial
	player->position.x = 200.0f;
    player->position.y = 375.0f;
    player->rect.x = player->position.x;
    player->rect.y = player->position.y;
    player->rect.width = (float) player->texture.width * 0.2;
    player->rect.height = (float) player->texture.height * 0.2;
    player->hearts = 3;
    player->active = true;
    player->velocity = (Vector2){0, 0};
    player->canJump = false;
	player->attacking = false;
    player->attackTime = 0;
    player->lastAttack = 0;
    player->hitbox = (Rectangle) {0, 0, 0, 0};
    player->facing = 0;

    return *player;
}

void IsPlayerAlive(Player *player) {
    if (player->hearts <= 0) {
        player->active = false;
    }
}

bool CanAttack(Player *player, float time) {
    if (IsKeyDown(KEY_ATTACK) && (time >= player->lastAttack + COOLDOWN_ATTACK) && player->attacking == false) {
        return true;
    }
    else {
        return false;
    }
}

void StartPlayerAttack(Player *player, Enemy *enemy) {
    if (player->facing == 0) {
        player->hitbox = (Rectangle) {
            (player->rect.x + player->rect.width),
            (player->rect.y + (player->rect.height * 0.1)),
            (player->rect.width * 1),
            (player->rect.height * 0.8)
        };
    }
    else if (player->facing == 1) {
        player->hitbox = (Rectangle) {
            (player->rect.x - (player->rect.width * 1)),
            (player->rect.y + (player->rect.height * 0.1)),
            (player->rect.width * 1),
            (player->rect.height * 0.8)
        };
    }

    player->attacking = true;
    player->attackTime = GetTime();

    if (CheckCollisionRecs(player->hitbox, enemy->rect)) {
        enemy->health -= 20;
        IsEnemyAlive(enemy);
    }
}

bool CanConcludeAttack(Player *player, float time) {
    if (player->attacking == true && (time >= player->attackTime + TIME_ATTACK)) {
        return true;
    }
    else {
        return false;
    }
}

void ConcludePlayerAttack(Player *player) {
    player->hitbox = (Rectangle) {player->rect.x, player->rect.y,0, 0};
    player->attacking = false;
    player->lastAttack = GetTime();
}
    