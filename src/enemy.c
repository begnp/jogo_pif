#include "enemy.h"
#include "player.h"

#define ENEMY_HOR_SPEED 80.0f

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
        enemy->active = true;
        enemy->velocity = (Vector2){0, 0};
        enemy->attacking = false;
        enemy->facing = 0;
        // enemy->vision = {};
    }

    return *enemy;
}

void IsEnemyAlive(Enemy *enemy) {
    if (enemy->health <= 0) {
        enemy->active = false;
    }
}

void EnemyVision(Enemy *enemy , Player *player) {
    float dt = GetFrameTime();
    enemy->vision = (Rectangle) {
        (enemy->rect.x - (enemy->rect.width * 2)),
        (enemy->rect.y),
        (enemy->rect.width * 5),
        (enemy->rect.height)
    };
    if (CheckCollisionRecs(enemy->vision, player->rect)) {
        if ((player->rect.x + (player->rect.width / 2)) > (enemy->rect.x + (enemy->rect.width * 0.55))) {
            enemy->facing = 0;
            enemy->velocity.x = ENEMY_HOR_SPEED;
            enemy->rect.x += enemy->velocity.x * dt;
        }
        else if ((player->rect.x + (player->rect.width / 2)) < (enemy->rect.x + (enemy->rect.width * 0.45))) {
            enemy->facing = 1;
            enemy->velocity.x = -ENEMY_HOR_SPEED;
            enemy->rect.x += enemy->velocity.x * dt;
        }
    }
}
