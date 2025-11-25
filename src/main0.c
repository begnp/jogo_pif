#include "camera.h"
#include "enemy.h"
#include "player.h"
#include "menu.h"
#include "map.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "score.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600

#define PLAYER_JUMP_SPEED -470.0f
#define PLAYER_HOR_SPEED 200.0f
#define GRAVITY 800.0f

#define KEY_ATTACK KEY_SPACE
#define KEY_JUMP KEY_W
#define KEY_RIGHT KEY_D
#define KEY_LEFT KEY_A

int main(void) {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Metroid Leveling - Demo");

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

    double inicioRun = 0;
    RunRecord records[5];
    int qtdRecords = 0;
    bool rankingCarregado = false;

    Player *helena = (Player *) malloc(sizeof(Player));
    *helena = InitPlayer(helena, texPlayerRight);

    helena->rect.x = 100.0f; 
    helena->rect.y = 400.0f; 
    
    Image imgEnemy0 = LoadImage("./assets/snorlax.png");

    Texture2D texEnem0 = LoadTextureFromImage(imgEnemy0);

    UnloadImage(imgEnemy0);

    Enemy *enemy0 = (Enemy *) malloc(sizeof(Enemy));
    *enemy0 = InitEnemy(enemy0, texEnem0, 0);
    
    Map map;
    InitMap(&map); 

    // bool LoadBoss = false;
    
    SetTargetFPS(60);

    Rectangle btnBack = { SCREEN_WIDTH/2 - 100, 400, 200, 50 };

    Camera2D camera = InitCamera((Vector2){helena->rect.x, helena->rect.y}, (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});
    
    while(!WindowShouldClose()) {

        double timer = GetTime();

        float dt = GetFrameTime();

        /* if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        } */

        if (currentScreen == EXIT) {
            break; 
        }
        
        switch(currentScreen) 
        {
            case MENU:
            case LEADERBOARD:
            case CREDITS:
                {   
                GameScreen proximaTela = UpdateMenu(&menu, currentScreen);
                
               
                if (proximaTela == GAMEPLAY) {
                    inicioRun = GetTime();
                    
                    helena->hearts = 3; 
                    helena->active = true;
                    helena->rect.x = 100.0f; 
                    helena->rect.y = 400.0f;
                }
                
                currentScreen = proximaTela;
            }  
                
                break;
            
            case GAMEOVER:
                if (CheckCollisionPointRec(GetMousePosition(), btnBack)) {
                    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {

                        helena->hearts = 3; 
                        helena->active = true;
                        helena->rect.x = 0; 
                        helena->rect.y = 520 - helena->rect.height; 
                        helena->velocity = (Vector2){0,0};
                        enemy0->active = true;
                        currentScreen = MENU; 
                    }
                }
                break;
                
            
        

            case GAMEPLAY:

                /* if (map.currentArea == 6 && LoadBoss == false) {
                    printf("vamos dar load nisso\n");
                } */

                if (helena->hearts <= 0){
                    float tempoSobrevivido = (float)(GetTime() - inicioRun);
                    SalvarTempoRun(tempoSobrevivido);
                    
                    rankingCarregado = false;
                    currentScreen = GAMEOVER;
                }

                helena->velocity.x = 0;
                
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
                
                helena->velocity.y += GRAVITY * dt;
                
                helena->rect.x += helena->velocity.x * dt;

                CheckMapTransition(&map, &helena->rect);

                if (map.currentArea == 1) {
                    if (helena->rect.x < 50.0f) {
                        helena->rect.x = 50.0f;
                    }
                }
                
                helena->rect.y += helena->velocity.y * dt;
                
                if (CheckCollisionRecs(helena->rect, map.platforms[0])) {
                    helena->rect.y = map.platforms[0].y - helena->rect.height;
                    helena->velocity.y = 0;
                    helena->canJump = true;
                }

                enemy0->velocity.y += GRAVITY * dt;

                enemy0->rect.x += enemy0->velocity.x * dt;
                enemy0->rect.y += enemy0->velocity.y * dt;

                if (CheckCollisionRecs(enemy0->rect, map.platforms[0])) {
                    enemy0->rect.y = map.platforms[0].y - enemy0->rect.height;
                    enemy0->velocity.y = 0;
                }
                
                for (int i = 1; i < map.platformsCount; i++) {
                    if (CheckCollisionRecs(helena->rect, map.platforms[i])) {
                        if (helena->velocity.y > 0) {
                            if (helena->rect.y + (helena->rect.height * 0.8) < map.platforms[i].y) {
                                helena->rect.y = map.platforms[i].y - helena->rect.height;
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

                enemy0->velocity.x = 0;
                if (enemy0->active == true) {
                    EnemyVision(enemy0, helena);
                }

                if (CanEnemyConcludeAttack(enemy0, timer)) {
                    ConcludeEnemyAttack(enemy0);
                }
                
                UpdateCameraToFollowPlayer(&camera, (Vector2){helena->rect.x, helena->rect.y}, SCREEN_WIDTH, SCREEN_HEIGHT, MAP_WIDTH, MAP_HEIGHT);

                if (IsKeyPressed(KEY_M)) currentScreen = MENU;
                
                break;

                default: break;
        }

        BeginDrawing();
        if (currentScreen == GAMEPLAY) {
            ClearBackground(BLACK); 
        } else {
            ClearBackground(menu.colorBgDark);
        }

        switch(currentScreen) 
        {
            case MENU:
            case CREDITS:
                DrawMenu(&menu, currentScreen);
                break;

            case LEADERBOARD:
                DrawMenu(&menu, currentScreen); 

                    if (!rankingCarregado) {
                        qtdRecords = CarregarTopTempos(records, 5);
                        rankingCarregado = true;
                    }

                    if (qtdRecords == 0) {
                        DrawText("Nenhum registro encontrado.", 350, 250, 20, GRAY);
                    }

                    for (int i = 0; i < qtdRecords; i++) {
                        char tempoTexto[20];
                        FormatarTempo(records[i].tempoSegundos, tempoTexto);

                        char linha[100];
                        sprintf(linha, "%d. %s .  .  .  .  .  .  .  . %s", i+1, records[i].nome, tempoTexto);
                        
                        DrawText(linha, 320, 180 + (i * 40), 20, menu.colorText);
                    }
                    

                    break;

            case GAMEOVER:
                
                DrawMapBackground(&map); 
                DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.8f));

                DrawText("FIM DE LINHA", SCREEN_WIDTH/2 - MeasureText("FIM DE LINHA", 40)/2, 200, 40, RED);

                Color btnColor = LIGHTGRAY;
                if (CheckCollisionPointRec(GetMousePosition(), btnBack)) btnColor = WHITE;
                
                DrawRectangleRec(btnBack, btnColor);
                DrawRectangleLinesEx(btnBack, 2, BLACK);
                
                const char* textBtn = "MENU PRINCIPAL";
                int textW = MeasureText(textBtn, 20);
                DrawText(textBtn, (int)(btnBack.x + btnBack.width/2 - textW/2), (int)(btnBack.y + 15), 20, BLACK);
                break;
            
            
            case GAMEPLAY:

                Rectangle rectsource = {0.0f, 0.0f, (float) helena->texture.width, (float) helena->texture.height};
                Rectangle rectdest = helena->rect;

                Rectangle rectsource_e = {0.0f, 0.0f, (float) enemy0->texture.width, (float) enemy0->texture.height};
                Rectangle rectdest_e = enemy0->rect;
                
                DrawMapBackground(&map);

                BeginMode2D(camera);

                    DrawMapPlatforms(&map);

                    if (enemy0->active == true) {
                        DrawRectangleRec(enemy0->vision, GRAY);
                        DrawTexturePro(
                            enemy0->texture,
                            rectsource_e,
                            rectdest_e,
                            (Vector2){0, 0},
                            0.0f,
                            WHITE
                        );
                        DrawRectangleRec(enemy0->hitbox, RED);
                        if (enemy0->delayAttack != 0)
                            DrawText("delay", enemy0->rect.x, enemy0->rect.y, 10, RED);
                    }

                    if (helena->active == true) {
                        DrawTexturePro(
                            helena->texture,
                            rectsource, rectdest, 
                            (Vector2){0, 0}, 
                            0.0f, 
                            WHITE
                        );

                        if (helena->attacking == true) {
                            DrawRectangleRec(helena->hitbox, BLUE);
                        }
                    }

                    DrawMapForeground(&map);
                    
                EndMode2D();

                    char text[20];
                    sprintf(text, "Vida: %d", helena->hearts);
                    DrawText(text, 15, 15, 30, RED);
                
                break;

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

    UnloadMap(&map);

    free(helena);
    free(enemy0);
    
    CloseWindow();
    
    return 0;
}