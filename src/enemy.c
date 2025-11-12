#include "enemy.h"

Enemy InitEnemy(Enemy *enemy, Texture2D initTex, int idEnemy) {

    if (idEnemy == 0) { // Inimigo básico
        enemy->id_enemy = idEnemy;
        enemy->texture = initTex; //textura inicial
        enemy->position.x = 600.0f;
        enemy->position.y = 305.0f;
        enemy->rect.x = enemy->position.x;
        enemy->rect.y = enemy->position.y;
        enemy->rect.width = (float) enemy->texture.width * 0.2;
        enemy->rect.height = (float) enemy->texture.height * 0.2;
        enemy->health = 50;
        enemy->velocity = (Vector2){0, 0};
        enemy->attacking = false;
        enemy->facing = 0;
        // enemy->vision = {};
    }

    return *enemy;
}
