#include "boss.h"
#include "player.h"
#include <stdio.h>

#define BOSS_HOR_SPEED 50.0f

#define BOSS_TIME_ATTACK 0.5
#define BOSS_COOLDOWN_ATTACK 0.4
#define BOSS_DELAY_ATTACK 0.5

Boss InitBoss(Boss *boss, Texture2D initTex) {
    boss->texture = initTex; //textura inicial
    boss->position.x = 600.0f;
    boss->position.y = 305.0f;
    boss->rect.x = boss->position.x;
    boss->rect.y = boss->position.y;
    boss->rect.width = (float) boss->texture.width * 0.12;
    boss->rect.height = (float) boss->texture.height * 0.12;
    boss->health = 50;
    boss->active = true;
    boss->velocity = (Vector2){0, 0};
    boss->attacking = false;
    boss->facing = 0;
    boss->delayAttack = 0;
    boss->targetInRange = false;

    return *boss;
}

void IsBossAlive(Boss *boss) {
    if (boss->health <= 0) {
        boss->active = false;
    }
}

void BossVision(Boss *boss , Player *player) {
    float dt = GetFrameTime();
    boss->vision = (Rectangle) {
        (boss->rect.x - (boss->rect.width * 2)),
        (boss->rect.y - 50),
        (boss->rect.width * 5),
        (50 + boss->rect.height)
    };
    if (CheckCollisionRecs(boss->vision, player->rect)) {
        if (boss->targetInRange == true) {
            DelayBossAttack(boss, player, GetTime());
        }
        else if ((player->rect.x + (player->rect.width / 2)) > (boss->rect.x + (boss->rect.width / 2))) {
            if ((player->rect.x + (player->rect.width / 2)) > (boss->rect.x + (boss->rect.width))) {
                boss->facing = 0;
                boss->velocity.x = BOSS_HOR_SPEED;
                boss->rect.x += boss->velocity.x * dt;
            }
            if ((player->rect.x + (player->rect.width / 2)) < (boss->rect.x + boss->rect.width + (boss->rect.width * 0.5))) {
                if (CanBossAttack(boss, player, GetTime())) {
                    boss->targetInRange = true;
                }
            }
        }
        else if ((player->rect.x + (player->rect.width / 2)) < (boss->rect.x + (boss->rect.width / 2))) {
            if ((player->rect.x + (player->rect.width / 2)) < boss->rect.x) {
                boss->facing = 1;
                boss->velocity.x = -BOSS_HOR_SPEED;
                boss->rect.x += boss->velocity.x * dt;
            }
            if ((player->rect.x + (player->rect.width / 2)) > (boss->rect.x - (boss->rect.width * 0.5))) {
                // printf("can attack?\n");
                if (CanBossAttack(boss, player, GetTime())) {
                    boss->targetInRange = true;
                    // printf("start attack\n");
                    // StartBossAttack(boss, player);
                }
            }
        }
    }
}

bool CanBossAttack(Boss *boss, Player *player, float time) {
    if ((time >= boss->lastAttack + BOSS_COOLDOWN_ATTACK) && boss->attacking == false) {
        if (boss->delayAttack == 0)
            boss->delayAttack = time;
        return true;
    }
    else {
        boss->delayAttack = 0;
        return false;
    }
}

void DelayBossAttack(Boss *boss, Player *player, float time) {
    if (time >= boss->delayAttack + BOSS_DELAY_ATTACK) {
        StartBossAttack(boss, player);
        boss->targetInRange = false;
    }
}

void StartBossAttack(Boss *boss, Player *player) {
    if (boss->facing == 0) {
        boss->hitbox = (Rectangle) {
            (boss->rect.x + (boss->rect.width / 2)),
            (boss->rect.y + (boss->rect.height * 0.1)),
            (boss->rect.width * 0.8),
            (boss->rect.height * 0.8)
        };
    }
    else if (boss->facing == 1) {
        boss->hitbox = (Rectangle) {
            (boss->rect.x - (boss->rect.width * 0.3)),
            (boss->rect.y + (boss->rect.height * 0.1)),
            (boss->rect.width * 0.8),
            (boss->rect.height * 0.8)
        };
    }

    boss->attacking = true;
    boss->attackTime = GetTime();
    boss->delayAttack = 0;

    if (CheckCollisionRecs(boss->hitbox, player->rect)) {
        player->hearts--;
        IsPlayerAlive(player);
    }
}

bool CanBossConcludeAttack(Boss *boss, float time) {
    if (boss->attacking == true && (time >= boss->attackTime + BOSS_TIME_ATTACK)) {
        return true;
    }
    else {
        return false;
    }
}

void ConcludeBossAttack(Boss *boss) {
    boss->hitbox = (Rectangle) {boss->rect.x, boss->rect.y,0, 0};
    boss->attacking = false;
    boss->lastAttack = GetTime();
}
