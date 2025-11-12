#include "player.h"

Player InitPlayer(Player *player, Texture2D initTex) {
    player->texture = initTex; //textura inicial
	player->position.x = 200.0f;
    player->position.y = 375.0f;
    player->rect.x = player->position.x;
    player->rect.y = player->position.y;
    player->rect.width = (float) player->texture.width * 0.2;
    player->rect.height = (float) player->texture.height * 0.2;
    player->hearts = 3;
    player->velocity = (Vector2){0, 0};
    player->canJump = false;
	player->attacking = false;
	player->facing = 0;

    return *player;
}