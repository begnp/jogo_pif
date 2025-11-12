#include "enemy.h"

Enemy InitEnemy(Enemy *enemy, Texture2D initTex, int idEnemy) {
    enemy->id_enemy = idEnemy;
    enemy->texture = initTex; //textura inicial
	enemy->position.x = 200.0f;
    enemy->position.y = 375.0f;
    enemy->rect.x = enemy->position.x;
    enemy->rect.y = enemy->position.y;
    enemy->rect.width = (float) enemy->texture.width * 0.2;
    enemy->rect.height = (float) enemy->texture.height * 0.2;
    enemy->health = 50;
    enemy->velocity = (Vector2){0, 0};
    enemy->canJump = false;
	enemy->attacking = false;
	enemy->facing = 0;

    return *enemy;
}
