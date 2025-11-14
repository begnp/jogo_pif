#include "camera.h"
#include "enemy.h"
#include "player.h"
#include "menu.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600

#define PLAYER_JUMP_SPEED -350.0f
#define PLAYER_HOR_SPEED 200.0f
#define GRAVITY 500.0f

#define KEY_ATTACK KEY_SPACE
#define KEY_JUMP KEY_W
#define KEY_RIGHT KEY_D
#define KEY_LEFT KEY_A

int main(void) {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Conceito 1: Saltador Quadrado");

    Texture2D menuBg = LoadTexture("assets/menu.png");
    Menu menu;

    InitMenu(&menu, SCREEN_WIDTH, SCREEN_HEIGHT, menuBg);
    
    GameScreen currentScreen = MENU; 

    Image player0 = LoadImage("./assets/Ellie_f0_right.png");
    Image player1 = LoadImage("./assets/Ellie_f0_left.png");
    
    Image player0_a = LoadImage("./assets/Ellie_f_a_right.png");
    Image player1_a = LoadImage("./assets/Ellie_f_a_left.png");
    
    Texture2D texPlayerRight = LoadTextureFromImage(player0);
    Texture2D texPlayerLeft = LoadTextureFromImage(player1);
    Texture2D texPlayerAttackRight = LoadTextureFromImage(player0_a);
    Texture2D texPlayerAttackLeft = LoadTextureFromImage(player1_a);

    UnloadImage(player0);
    UnloadImage(player1);
    UnloadImage(player0_a);
    UnloadImage(player1_a);

    Player *helena = (Player *) malloc(sizeof(Player));
    *helena = InitPlayer(helena, texPlayerRight);


    Image imgEnemy0 = LoadImage("./assets/snorlax.png");

    Texture2D texEnem0 = LoadTextureFromImage(imgEnemy0);

    UnloadImage(imgEnemy0);

    Enemy *enemy0 = (Enemy *) malloc(sizeof(Enemy));
    *enemy0 = InitEnemy(enemy0, texEnem0, 0);
    
    Rectangle floor = {0, 450, SCREEN_WIDTH, 20};
    
    Rectangle platforms[] = {
        {300, 350, 100, 20},
        {100, 300, 200, 20},
        {400, 200, 150, 20},
        {500, 100, 100, 20}
    };
    int numPlatforms = sizeof(platforms) / sizeof(platforms[0]);
    
    SetTargetFPS(60);

    Camera2D camera = InitCamera((Vector2){helena->rect.x, helena->rect.y}, (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});
    
    while(!WindowShouldClose()) {

        double timer = GetTime();

        float dt = GetFrameTime();

        /* if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        } */
        
        switch(currentScreen) 
        {
            case MENU:
            case LEADERBOARD:
            case CREDITS:
                currentScreen = UpdateMenu(&menu, currentScreen);
                break;

            case GAMEPLAY:
                helena->velocity.x = 0;
                enemy0->velocity.x = 0;
                
                if (IsKeyDown(KEY_RIGHT)) {
                    helena->velocity.x = PLAYER_HOR_SPEED;
                    if (helena->facing == 1 && helena->attacking == false) {
                        helena->texture = texPlayerRight;
                    }
                    helena->facing = 0;
                }

                if (IsKeyDown(KEY_LEFT)) {
                    helena->velocity.x = -PLAYER_HOR_SPEED;
                    if (helena->facing == 0 && helena->attacking == false) {
                        helena->texture = texPlayerLeft;
                    }
                    helena->facing = 1;
                }
                
                if (IsKeyDown(KEY_JUMP) && helena->canJump) {
                    helena->velocity.y = PLAYER_JUMP_SPEED;
                    helena->canJump = false;
                }

                /* if (IsKeyDown(KEY_ATTACK) && helena->attacking == false) {
                    attackTime = timer;
                    helena->attacking = true;
                    if (helena->facing == 0) {
                        helena->texture = texPlayerAttackRight;
                    }
                    else if (helena->facing == 1) {
                        helena->texture = texPlayerAttackLeft;
                    }
                } */
                
                helena->velocity.y += GRAVITY * dt;
                
                helena->rect.x += helena->velocity.x * dt;
                helena->rect.y += helena->velocity.y * dt;
                
                if (CheckCollisionRecs(helena->rect, floor)) {
                    helena->rect.y = floor.y - helena->rect.height;
                    helena->velocity.y = 0;
                    helena->canJump = true;
                }

                enemy0->velocity.y += GRAVITY * dt;

                enemy0->rect.x += enemy0->velocity.x * dt;
                enemy0->rect.y += enemy0->velocity.y * dt;

                if (CheckCollisionRecs(enemy0->rect, floor)) {
                    enemy0->rect.y = floor.y - enemy0->rect.height;
                    enemy0->velocity.y = 0;
                }
                
                for (int i = 0; i < numPlatforms; i++) {
                    if (CheckCollisionRecs(helena->rect, platforms[i])) {
                        if (helena->velocity.y > 0) {
                            if (helena->rect.y + (helena->rect.height * 0.8) < platforms[i].y) {
                                helena->rect.y = platforms[i].y - helena->rect.height;
                                helena->velocity.y = 0;
                                helena->canJump = true;
                            }
                        }
                    }
                }

                if (CanAttack(helena, timer)) {
                    StartPlayerAttack(helena, enemy0);
                    if (helena->facing == 0) {
                        helena->texture = texPlayerAttackRight;
                    }
                    else if (helena->facing == 1) {
                        helena->texture = texPlayerAttackLeft;
                    }
                }

                if (CanConcludeAttack(helena, timer)) {
                    ConcludePlayerAttack(helena);
                    if (helena->facing == 0) {
                        helena->texture = texPlayerRight;
                    }
                    else if (helena->facing == 1) {
                        helena->texture = texPlayerLeft;
                    }
                }

                EnemyVision(enemy0, helena);
                
                UpdateCameraToFollowPlayer(&camera, (Vector2){helena->rect.x, helena->rect.y}, SCREEN_WIDTH, SCREEN_HEIGHT);

                if (IsKeyPressed(KEY_M)) currentScreen = MENU;
                
                default: break;
        }


        BeginDrawing();
        ClearBackground(SKYBLUE);

        switch(currentScreen) 
        {
            case MENU:
            case LEADERBOARD:
            case CREDITS:
                DrawMenu(&menu, currentScreen);
                break;

            case GAMEPLAY:
                BeginMode2D(camera);
                    
                    Rectangle rectsource = {0.0f, 0.0f, (float) helena->texture.width, (float) helena->texture.height};
                    Rectangle rectdest = helena->rect;

                    Rectangle rectsource_e = {0.0f, 0.0f, (float) enemy0->texture.width, (float) enemy0->texture.height};
                    Rectangle rectdest_e = enemy0->rect;

                    DrawRectangleRec(enemy0->vision, GRAY);
                    //DrawRectangleRec(helena->rect, WHITE);
                    DrawTexturePro(helena->texture, rectsource, rectdest, (Vector2){0, 0}, 0.0f, WHITE);

                    // DrawRectangleRec(enemy0->rect, WHITE);
                    if (enemy0->active == true) {
                        DrawTexturePro(enemy0->texture, rectsource_e, rectdest_e, (Vector2){0, 0}, 0.0f, WHITE);
                    }
                    
                    if (helena->attacking == true) {
                        DrawRectangleRec(helena->hitbox, RED);
                    }

                    DrawRectangleRec(floor, GREEN);
                    
                    for (int i = 0; i < numPlatforms; i++) {
                        DrawRectangleRec(platforms[i], GRAY);
                    }
                    
                EndMode2D();
                default: break;
        }
        
        EndDrawing();
        
    }
    
    ToggleBorderlessWindowed();

    UnloadTexture(texPlayerRight);
    UnloadTexture(texPlayerLeft);
    UnloadTexture(texPlayerAttackRight);
    UnloadTexture(texPlayerAttackLeft);

    UnloadTexture(texEnem0);
    UnloadTexture(menuBg);

    free(helena);
    free(enemy0);
    
    CloseWindow();
    
    return 0;
}