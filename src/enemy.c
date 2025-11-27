#include "enemy.h"
#include "player.h"
#include <stdio.h>

#define ENEMY_HOR_SPEED 50.0f

#define ENEMY_TIME_ATTACK 0.5
#define ENEMY_COOLDOWN_ATTACK 0.4
#define ENEMY_DELAY_ATTACK 0.4

Enemy InitEnemy(Enemy *enemy, Texture2D initTex, int idEnemy, float posX, float posY) {

    if (idEnemy == 0) { // Inimigo básico
        enemy->id_enemy = idEnemy;
        enemy->currentTexture = initTex; //textura inicial
        enemy->position.x = posX;
        enemy->position.y = posY;
        enemy->rect.x = enemy->position.x;
        enemy->rect.y = enemy->position.y;
        enemy->rect.width = (float) enemy->currentTexture.width * 0.2;
        enemy->rect.height = (float) enemy->currentTexture.height * 0.2;
        enemy->health = 50;
        enemy->active = true;
        enemy->velocity = (Vector2){0, 0};
        enemy->attacking = false;
        enemy->facing = 0;
        enemy->delayAttack = 0;
        enemy->targetInRange = false;
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
        (enemy->rect.x - (enemy->rect.width * 3)),
        (enemy->rect.y - 50),
        (enemy->rect.width * 7),
        (50 + enemy->rect.height)
    };
    if (CheckCollisionRecs(enemy->vision, player->rect)) {
        if (enemy->targetInRange == true) {
            DelayEnemyAttack(enemy, player, GetTime());
        }
        else if ((player->rect.x + (player->rect.width / 2)) > (enemy->rect.x + (enemy->rect.width / 2))) {
            if ((player->rect.x + (player->rect.width / 2)) > (enemy->rect.x + (enemy->rect.width))) {
                enemy->facing = 0;
                enemy->velocity.x = ENEMY_HOR_SPEED;
                enemy->rect.x += enemy->velocity.x * dt;
            }
            if ((player->rect.x + (player->rect.width / 2)) < (enemy->rect.x + enemy->rect.width + (enemy->rect.width * 0.5))) {
                if (CanEnemyAttack(enemy, player, GetTime())) {
                    enemy->targetInRange = true;
                }
            }
        }
        else if ((player->rect.x + (player->rect.width / 2)) < (enemy->rect.x + (enemy->rect.width / 2))) {
            if ((player->rect.x + (player->rect.width / 2)) < enemy->rect.x) {
                enemy->facing = 1;
                enemy->velocity.x = -ENEMY_HOR_SPEED;
                enemy->rect.x += enemy->velocity.x * dt;
            }
            if ((player->rect.x + (player->rect.width / 2)) > (enemy->rect.x - (enemy->rect.width * 0.5))) {
                // printf("can attack?\n");
                if (CanEnemyAttack(enemy, player, GetTime())) {
                    enemy->targetInRange = true;
                    // printf("start attack\n");
                    // StartEnemyAttack(enemy, player);
                }
            }
        }
    }
}

bool CanEnemyAttack(Enemy *enemy, Player *player, float time) {
    if ((time >= enemy->lastAttack + ENEMY_COOLDOWN_ATTACK) && enemy->attacking == false) {
        if (enemy->delayAttack == 0)
            enemy->delayAttack = time;
        return true;
    }
    else {
        enemy->delayAttack = 0;
        return false;
    }
}

void DelayEnemyAttack(Enemy *enemy, Player *player, float time) {
    if (time >= enemy->delayAttack + ENEMY_DELAY_ATTACK) {
        StartEnemyAttack(enemy, player);
        enemy->targetInRange = false;
    }
}

void StartEnemyAttack(Enemy *enemy, Player *player) {
    if (enemy->facing == 0) {
        enemy->hitbox = (Rectangle) {
            (enemy->rect.x + (enemy->rect.width * 0.6)),
            (enemy->rect.y + (enemy->rect.height * 0.1)),
            (enemy->rect.width * 0.8),
            (enemy->rect.height * 0.8)
        };
    }
    else if (enemy->facing == 1) {
        enemy->hitbox = (Rectangle) {
            (enemy->rect.x - (enemy->rect.width * 0.5)),
            (enemy->rect.y + (enemy->rect.height * 0.1)),
            (enemy->rect.width * 0.8),
            (enemy->rect.height * 0.8)
        };
    }

    enemy->attacking = true;
    enemy->attackTime = GetTime();
    enemy->delayAttack = 0;

    if (CheckCollisionRecs(enemy->hitbox, player->rect)) {
        player->hearts--;
        IsPlayerAlive(player);
    }
}

bool CanEnemyConcludeAttack(Enemy *enemy, float time) {
    if (enemy->attacking == true && (time >= enemy->attackTime + ENEMY_TIME_ATTACK)) {
        return true;
    }
    else {
        return false;
    }
}

void ConcludeEnemyAttack(Enemy *enemy) {
    enemy->hitbox = (Rectangle) {enemy->rect.x, enemy->rect.y,0, 0};
    enemy->attacking = false;
    enemy->lastAttack = GetTime();
}
