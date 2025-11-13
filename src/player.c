#include "player.h"
#include "enemy.h"

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
    player->hitbox = (Rectangle) {0, 0, 0, 0};
    player->facing = 0;

    return *player;
}

void IsplayerAttack(Player *player, Enemy *enemy) {
    if (IsKeyDown(KEY_SPACE)){
        if (player->facing == 0) {
            player->hitbox = (Rectangle) {
                (player->rect.x + player->rect.width),
                (player->rect.y + (player->rect.height * 0.1)),
                (player->rect.width * 0.5),
                (player->rect.height * 0.5)
            };
        }
        else if (player->facing == 1) {
            player->hitbox = (Rectangle) {
                (player->rect.x - (player->rect.width * 0.3)),
                (player->rect.y + (player->rect.height * 0.1)),
                (player->rect.width * 0.5),
                (player->rect.height * 0.5)
            };
        }
        if (CheckCollisionRecs(player->hitbox, enemy->rect)) {
            enemy->health -= 2;
        }
    }
    else {
        player->hitbox = (Rectangle) {player->rect.x, player->rect.y,0, 0};
    }
}