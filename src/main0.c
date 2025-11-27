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

#define AMOUNT_AREAS 6

#define AMOUNT_ENEMY_AREA_1 2
#define AMOUNT_ENEMY_AREA_2 4
#define AMOUNT_ENEMY_AREA_3 2
#define AMOUNT_ENEMY_AREA_4 4
#define AMOUNT_ENEMY_AREA_5 2
#define AMOUNT_ENEMY_AREA_6 9


int main(void) {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Metroid Leveling - Demo");

    InitAudioDevice();
    
    Music musicMenu = LoadMusicStream("assets/TrilhaSonoraMenu.mp3");
    Music musicGame = LoadMusicStream("assets/TrilhaSonoraMapa.mp3");
    Music musicWin = LoadMusicStream("assets/TrilhaSonoraFinal");
    
    musicMenu.looping = true;
    musicGame.looping = true;
    
    PlayMusicStream(musicMenu);
    
    float volumeGame = 0.0f; 

    float introTimer = 0.0f;
    int introPhase = 0; 

    Texture2D introImg1 = LoadTexture("assets/IntroParte1.png");
    Texture2D introImg2 = LoadTexture("assets/IntroParte2.png");
    Texture2D introImg3 = LoadTexture("assets/IntroParte3.png");
    Texture2D introImg4 = LoadTexture("assets/IntroParte4.png");
    Texture2D introImg5 = LoadTexture("assets/IntroParte5.png");
    
    Texture2D menuBg = LoadTexture("assets/menu.png");
    Menu menu;

    InitMenu(&menu, SCREEN_WIDTH, SCREEN_HEIGHT, menuBg);
    
    GameScreen currentScreen = INTRO; 

    Image player_idle = LoadImage("./assets/helena/idle.png");
    Image player_run0 = LoadImage("./assets/helena/run0.png");
    Image player_run1 = LoadImage("./assets/helena/run1.png");
    Image player_run2 = LoadImage("./assets/helena/run2.png");
    Image player_run3 = LoadImage("./assets/helena/run3.png");
    Image player_attack0 = LoadImage("./assets/helena/attack0.png");
    Image player_attack1 = LoadImage("./assets/helena/attack1.png");
    Image player_attack2 = LoadImage("./assets/helena/attack2.png");
    Image player_jump0 = LoadImage("./assets/helena/jump0.png");
    Image player_jump1 = LoadImage("./assets/helena/jump1.png");
    Image player_jump2 = LoadImage("./assets/helena/jump2.png");

    Texture2D texPlayerIdle = LoadTextureFromImage(player_idle);
    Texture2D texPlayerRun0 = LoadTextureFromImage(player_run0);
    Texture2D texPlayerRun1 = LoadTextureFromImage(player_run1);
    Texture2D texPlayerRun2 = LoadTextureFromImage(player_run2);
    Texture2D texPlayerRun3 = LoadTextureFromImage(player_run3);
    Texture2D texPlayerAttack0 = LoadTextureFromImage(player_attack0);
    Texture2D texPlayerAttack1 = LoadTextureFromImage(player_attack1);
    Texture2D texPlayerAttack2 = LoadTextureFromImage(player_attack2);
    Texture2D texPlayerJump0 = LoadTextureFromImage(player_jump0);
    Texture2D texPlayerJump1 = LoadTextureFromImage(player_jump1);
    Texture2D texPlayerJump2 = LoadTextureFromImage(player_jump2);

    UnloadImage(player_idle);
    UnloadImage(player_run0);
    UnloadImage(player_run1);
    UnloadImage(player_run2);
    UnloadImage(player_run3);
    UnloadImage(player_attack0);
    UnloadImage(player_attack1);
    UnloadImage(player_attack2);
    UnloadImage(player_jump0);
    UnloadImage(player_jump1);
    UnloadImage(player_jump2);


    double inicioRun = 0;
    ScoreNode *listaScores = NULL;
    bool rankingCarregado = false;

    Player *helena = (Player *) malloc(sizeof(Player));
    *helena = InitPlayer(helena, texPlayerIdle);

    helena->idleTexture = texPlayerIdle;

    helena->runTextures[0] = texPlayerRun0;
    helena->runTextures[1] = texPlayerRun1;
    helena->runTextures[2] = texPlayerRun2;
    helena->runTextures[3] = texPlayerRun3;

    helena->attackTextures[0] = texPlayerAttack0;
    helena->attackTextures[1] = texPlayerAttack1;
    helena->attackTextures[2] = texPlayerAttack2;

    helena->jumpTextures[0] = texPlayerJump0;
    helena->jumpTextures[1] = texPlayerJump1;
    helena->jumpTextures[2] = texPlayerJump2;

    helena->frameSpeed = 0.15f;
    helena->frameTimer = 0.0f;
    helena->currentFrame = 0;

    helena->rect.x = 100.0f; 
    helena->rect.y = 400.0f; 

    bool rectChangeToAttack = false;

    Image enemy_idle = LoadImage("./assets/enemy/idle.png");
    Image enemy_run0 = LoadImage("./assets/enemy/run2.png");
    Image enemy_run1 = LoadImage("./assets/enemy/run3.png");
    Image enemy_run2 = LoadImage("./assets/enemy/run2.png");
    Image enemy_run3 = LoadImage("./assets/enemy/run3.png");
    Image enemy_attack0 = LoadImage("./assets/enemy/attack0.png");
    Image enemy_attack1 = LoadImage("./assets/enemy/attack1.png");
    Image enemy_attack2 = LoadImage("./assets/enemy/attack2.png");

    Texture2D texEnemyIdle = LoadTextureFromImage(enemy_idle);
    Texture2D texEnemyRun0 = LoadTextureFromImage(enemy_run0);
    Texture2D texEnemyRun1 = LoadTextureFromImage(enemy_run1);
    Texture2D texEnemyRun2 = LoadTextureFromImage(enemy_run2);
    Texture2D texEnemyRun3 = LoadTextureFromImage(enemy_run3);
    Texture2D texEnemyAttack0 = LoadTextureFromImage(enemy_attack0);
    Texture2D texEnemyAttack1 = LoadTextureFromImage(enemy_attack1);
    Texture2D texEnemyAttack2 = LoadTextureFromImage(enemy_attack2);

    UnloadImage(enemy_idle);
    UnloadImage(enemy_run0);
    UnloadImage(enemy_run1);
    UnloadImage(enemy_run2);
    UnloadImage(enemy_run3);
    UnloadImage(enemy_attack0);
    UnloadImage(enemy_attack1);
    UnloadImage(enemy_attack2);
    
    Image imgEnemy0 = LoadImage("./assets/snorlax.png");

    Texture2D texEnem0 = LoadTextureFromImage(imgEnemy0);

    UnloadImage(imgEnemy0);
    
    Map map;
    InitMap(&map); 

    Vector2 **enemiesManager = (Vector2 **) malloc(AMOUNT_AREAS * sizeof(Vector2));
    enemiesManager[0] = (Vector2 *) malloc((AMOUNT_ENEMY_AREA_1) * sizeof(Vector2));
    enemiesManager[1] = (Vector2 *) malloc((AMOUNT_ENEMY_AREA_2) *sizeof(Vector2));
    enemiesManager[2] = (Vector2 *) malloc((AMOUNT_ENEMY_AREA_3) *sizeof(Vector2));
    enemiesManager[3] = (Vector2 *) malloc((AMOUNT_ENEMY_AREA_4) *sizeof(Vector2));
    enemiesManager[4] = (Vector2 *) malloc((AMOUNT_ENEMY_AREA_5) *sizeof(Vector2));
    enemiesManager[5] = (Vector2 *) malloc((AMOUNT_ENEMY_AREA_6) *sizeof(Vector2));
    
    // Area 1
    enemiesManager[0][0].x = 500;
    enemiesManager[0][0].y = 500;

    enemiesManager[0][1].x = 700;
    enemiesManager[0][1].y = 500;

    // Area 2
    enemiesManager[1][0].x = 100;
    enemiesManager[1][0].y = 320;

    enemiesManager[1][1].x = 420;
    enemiesManager[1][1].y = 260;

    enemiesManager[1][2].x = 420;
    enemiesManager[1][2].y = 110;

    enemiesManager[1][3].x = 820;
    enemiesManager[1][3].y = 210;

    // Area 3


    // Area 4
    enemiesManager[3][0].x = 100;
    enemiesManager[3][0].y = 350;

    enemiesManager[3][1].x = 420;
    enemiesManager[3][1].y = 420;

    enemiesManager[3][2].x = 420;
    enemiesManager[3][2].y = 230;

    enemiesManager[3][3].x = 750;
    enemiesManager[3][3].y = 550;

    // Area 5

    
    // Area 6
    enemiesManager[5][0].x = 150;
    enemiesManager[5][0].y = 430;

    enemiesManager[5][1].x = 150;
    enemiesManager[5][1].y = 310;

    enemiesManager[5][2].x = 150;
    enemiesManager[5][2].y = 190;
    
    enemiesManager[5][3].x = 450;
    enemiesManager[5][3].y = 430;
    
    enemiesManager[5][4].x = 450;
    enemiesManager[5][4].y = 310;
    
    enemiesManager[5][5].x = 450;
    enemiesManager[5][5].y = 190;
    
    enemiesManager[5][6].x = 750;
    enemiesManager[5][6].y = 430;
    
    enemiesManager[5][7].x = 750;
    enemiesManager[5][7].y = 310;
    
    enemiesManager[5][8].x = 750;
    enemiesManager[5][8].y = 190;

    int *enemiesStarted = (int *) malloc(sizeof(int));
    *enemiesStarted = 0;
    Enemy **enemyList = NULL;
    
    SetTargetFPS(60);

    Rectangle btnBack = { SCREEN_WIDTH/2 - 100, 400, 200, 50 };

    Camera2D camera = InitCamera((Vector2){helena->rect.x, helena->rect.y}, (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});
    
    while(!WindowShouldClose()) {

        double timer = GetTime();

        float dt = GetFrameTime();

        if (currentScreen == EXIT) {
            break; 
        }
        
        switch(currentScreen) 
        {
            case INTRO:
                {
                    UpdateMusicStream(musicMenu);
                    
                    introTimer += dt;

                    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
                        currentScreen = MENU;
                    }

                    if (introPhase == 0) {
                        if (introTimer > 3.0f) {
                            introPhase = 1;
                            introTimer = 0; 
                        }
                    } 
                    else if (introPhase == 1) {
                        if (introTimer > 7.0f) {
                            introPhase = 2;
                            introTimer = 0;
                        }
                    }
                    else if (introPhase == 2) {
                        if (introTimer > 9.0f) {
                            introPhase = 3; 
                            introTimer = 0;
                        }
                    }
                    else if (introPhase == 3) {
                        if (introTimer > 9.0f) {
                            introPhase = 4;
                            introTimer = 0;
                        }
                    }
                    else if (introPhase == 4) {
                        if (introTimer > 12.0f) {
                            introPhase = 5;
                            introTimer = 0;
                        }
                    }
                    else if (introPhase == 5) {
                        if (introTimer > 16.0f) {
                            currentScreen = MENU;
                        }
                    }
                }
                break;

            case MENU:
            case LEADERBOARD:
            case CREDITS:
                {   
                    UpdateMusicStream(musicMenu);

                    GameScreen proximaTela = UpdateMenu(&menu, currentScreen);
                
                    if (proximaTela == GAMEPLAY) {
                        
                        StopMusicStream(musicMenu);
                        PlayMusicStream(musicGame);
                        volumeGame = 0.0f; 
                        SetMusicVolume(musicGame, volumeGame);

                        inicioRun = GetTime();
                        
                        helena->hearts = 3; 
                        helena->active = true;
                        helena->rect.x = 100.0f; 
                        helena->rect.y = 400.0f;
                    }

                    if (currentScreen == LEADERBOARD && proximaTela != LEADERBOARD) {
                        if (listaScores != NULL) {
                            LiberarLista(listaScores);
                            listaScores = NULL;
                        }
                        rankingCarregado = false;
                    }
                
                    currentScreen = proximaTela;
                }  
                break;
            
            case GAMEOVER:
                if (CheckCollisionPointRec(GetMousePosition(), btnBack)) {
                    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {

                        StopMusicStream(musicGame);
                        PlayMusicStream(musicMenu);

                        helena->hearts = 3; 
                        helena->active = true;
                        helena->rect.x = 0; 
                        helena->rect.y = 520 - helena->rect.height; 
                        helena->velocity = (Vector2){0,0};
                        for (int i = 0; i < *enemiesStarted; i++) {
                            enemyList[i]->active = true;
                        }
                        *enemiesStarted = 0;
                        
                        currentScreen = MENU; 
                    }
                }
                break;
                
            
        

            case GAMEPLAY:

                UpdateMusicStream(musicGame);
                
                if (volumeGame < 1.0f) {
                    volumeGame += 0.3f * dt; 
                    if (volumeGame > 1.0f) volumeGame = 1.0f;
                    SetMusicVolume(musicGame, volumeGame);
                }

                if (map.currentArea == 1 && *enemiesStarted == 0) {
                    enemyList = (Enemy **) malloc(AMOUNT_ENEMY_AREA_1 * sizeof(Enemy*));
                    for (int i = 0; i < AMOUNT_ENEMY_AREA_1; i++) {
                        enemyList[i] = (Enemy *) malloc(sizeof(Enemy));
                        *(enemyList[i]) = InitEnemy(enemyList[i], texEnemyIdle, 0, enemiesManager[0][i].x, enemiesManager[0][i].y);
                        *enemiesStarted = AMOUNT_ENEMY_AREA_1;

                        enemyList[i]->idleTexture = texEnemyIdle;

                        enemyList[i]->runTextures[0] = texEnemyRun0;
                        enemyList[i]->runTextures[1] = texEnemyRun1;
                        enemyList[i]->runTextures[2] = texEnemyRun2;
                        enemyList[i]->runTextures[3] = texEnemyRun3;

                        enemyList[i]->attackTextures[0] = texEnemyAttack0;
                        enemyList[i]->attackTextures[1] = texEnemyAttack1;
                        enemyList[i]->attackTextures[2] = texEnemyAttack2;

                        enemyList[i]->frameSpeed = 0.3f;
                        enemyList[i]->frameTimer = 0.0f;
                        enemyList[i]->currentFrame = 0;
                    }
                }
                else if (map.currentArea == 2 && *enemiesStarted == 0) {
                    enemyList = (Enemy **) malloc(AMOUNT_ENEMY_AREA_2 * sizeof(Enemy*));
                    for (int i = 0; i < AMOUNT_ENEMY_AREA_2; i++) {
                        enemyList[i] = (Enemy *) malloc(sizeof(Enemy));
                        *(enemyList[i]) = InitEnemy(enemyList[i], texEnemyIdle, 0, enemiesManager[1][i].x, enemiesManager[1][i].y);
                        *enemiesStarted = AMOUNT_ENEMY_AREA_2;

                        enemyList[i]->idleTexture = texEnemyIdle;

                        enemyList[i]->runTextures[0] = texEnemyRun0;
                        enemyList[i]->runTextures[1] = texEnemyRun1;
                        enemyList[i]->runTextures[2] = texEnemyRun2;
                        enemyList[i]->runTextures[3] = texEnemyRun3;

                        enemyList[i]->attackTextures[0] = texEnemyAttack0;
                        enemyList[i]->attackTextures[1] = texEnemyAttack1;
                        enemyList[i]->attackTextures[2] = texEnemyAttack2;

                        enemyList[i]->frameSpeed = 0.3f;
                        enemyList[i]->frameTimer = 0.0f;
                        enemyList[i]->currentFrame = 0;
                    }
                }
                else if (map.currentArea == 4 && *enemiesStarted == 0) {
                    enemyList = (Enemy **) malloc(AMOUNT_ENEMY_AREA_4 * sizeof(Enemy*));
                    for (int i = 0; i < AMOUNT_ENEMY_AREA_4; i++) {
                        enemyList[i] = (Enemy *) malloc(sizeof(Enemy));
                        *(enemyList[i]) = InitEnemy(enemyList[i], texEnemyIdle, 0, enemiesManager[3][i].x, enemiesManager[3][i].y);
                        *enemiesStarted = AMOUNT_ENEMY_AREA_4;

                        enemyList[i]->idleTexture = texEnemyIdle;

                        enemyList[i]->runTextures[0] = texEnemyRun0;
                        enemyList[i]->runTextures[1] = texEnemyRun1;
                        enemyList[i]->runTextures[2] = texEnemyRun2;
                        enemyList[i]->runTextures[3] = texEnemyRun3;

                        enemyList[i]->attackTextures[0] = texEnemyAttack0;
                        enemyList[i]->attackTextures[1] = texEnemyAttack1;
                        enemyList[i]->attackTextures[2] = texEnemyAttack2;

                        enemyList[i]->frameSpeed = 0.3f;
                        enemyList[i]->frameTimer = 0.0f;
                        enemyList[i]->currentFrame = 0;
                    }
                }
                else if (map.currentArea == 6 && *enemiesStarted == 0) {
                    enemyList = (Enemy **) malloc(AMOUNT_ENEMY_AREA_6 * sizeof(Enemy*));
                    for (int i = 0; i < AMOUNT_ENEMY_AREA_6; i++) {
                        enemyList[i] = (Enemy *) malloc(sizeof(Enemy));
                        *(enemyList[i]) = InitEnemy(enemyList[i], texEnemyIdle, 0, enemiesManager[5][i].x, enemiesManager[5][i].y);
                        *enemiesStarted = AMOUNT_ENEMY_AREA_6;

                        enemyList[i]->idleTexture = texEnemyIdle;

                        enemyList[i]->runTextures[0] = texEnemyRun0;
                        enemyList[i]->runTextures[1] = texEnemyRun1;
                        enemyList[i]->runTextures[2] = texEnemyRun2;
                        enemyList[i]->runTextures[3] = texEnemyRun3;

                        enemyList[i]->attackTextures[0] = texEnemyAttack0;
                        enemyList[i]->attackTextures[1] = texEnemyAttack1;
                        enemyList[i]->attackTextures[2] = texEnemyAttack2;

                        enemyList[i]->frameSpeed = 0.3f;
                        enemyList[i]->frameTimer = 0.0f;
                        enemyList[i]->currentFrame = 0;
                    }
                }

                if (helena->hearts <= 0){
                    float tempoSobrevivido = (float)(GetTime() - inicioRun);
                    SalvarTempoRun(tempoSobrevivido);
                    
                    rankingCarregado = false;
                    currentScreen = GAMEOVER;
                }

                if (helena.killCount >= 20) {

                    StopMusicStream(musicGame); 
                    PlayMusicStream(musicWin); 

                    currentScreen = CREDITS; 
                }

                helena->velocity.x = 0;

                bool isMoving = false;
                
                if (IsKeyDown(KEY_RIGHT)) {
                    helena->velocity.x = PLAYER_HOR_SPEED;
                    helena->facing = 0;
                    isMoving = true;
                }

                if (IsKeyDown(KEY_LEFT)) {
                    helena->velocity.x = -PLAYER_HOR_SPEED;
                    helena->facing = 1;
                    isMoving = true;
                }

                // Animações da Helena
                if (helena->attacking) {
                    helena->frameTimer += dt;
                    
                    float attackFrameSpeed = 0.12f; 

                    if (helena->frameTimer >= attackFrameSpeed) {
                        helena->frameTimer = 0.0f;
                        helena->currentFrame++;
                        
                        if (helena->currentFrame > 2) {
                            helena->currentFrame = 0; 
                        }
                        
                        helena->currentTexture = helena->attackTextures[helena->currentFrame];
                    }
                }
                else if (helena->velocity.y > 200) {
                    helena->currentTexture = helena->jumpTextures[2];
                }
                else if (helena->velocity.y >= -200 && helena->velocity.y <= 200 && helena->velocity.y != 0) {
                    helena->currentTexture = helena->jumpTextures[1];
                }
                else if (helena->velocity.y < -200) {
                    helena->currentTexture = helena->jumpTextures[0];
                }
                else if (isMoving && !helena->attacking && helena->canJump) {
                    helena->frameTimer += dt;
                    
                    if (helena->frameTimer >= helena->frameSpeed) {
                        helena->frameTimer = 0.0f;
                        helena->currentFrame++;
                        
                        if (helena->currentFrame > 3) {
                            helena->currentFrame = 0;
                        }
                        
                        helena->currentTexture = helena->runTextures[helena->currentFrame];
                    }
                } 
                else {
                    helena->currentTexture = helena->idleTexture; 
                    helena->currentFrame = 0;
                }

                // Animações do inimigo
                for (int i = 0; i < *enemiesStarted; i++) {
                    if (enemyList[i]->attacking) {
                        enemyList[i]->frameTimer += dt;
                    
                        float attackFrameSpeed = 0.15f; 

                        if (enemyList[i]->frameTimer >= attackFrameSpeed) {
                            enemyList[i]->frameTimer = 0.0f;
                            enemyList[i]->currentFrame++;
                            
                            if (enemyList[i]->currentFrame > 2) {
                                enemyList[i]->currentFrame = 0; 
                            }
                            
                            enemyList[i]->currentTexture = enemyList[i]->attackTextures[enemyList[i]->currentFrame];
                        }
                    }
                    else if (enemyList[i]->velocity.x != 0 && !enemyList[i]->attacking) {
                        enemyList[i]->frameTimer += dt;

                        if (enemyList[i]->frameTimer >= enemyList[i]->frameSpeed) {
                            enemyList[i]->frameTimer = 0.0f;
                            enemyList[i]->currentFrame++;
                            
                            if (enemyList[i]->currentFrame > 3) {
                                enemyList[i]->currentFrame = 0; 
                            }
                            
                            enemyList[i]->currentTexture = enemyList[i]->runTextures[enemyList[i]->currentFrame];
                        }
                    }
                    else {
                        enemyList[i]->currentTexture = enemyList[i]->idleTexture; 
                        enemyList[i]->currentFrame = 0;
                    }
                }
                
                if (IsKeyDown(KEY_JUMP) && helena->canJump) {
                    helena->velocity.y = PLAYER_JUMP_SPEED;
                    helena->canJump = false;
                }
                
                helena->velocity.y += GRAVITY * dt;
                
                helena->rect.x += helena->velocity.x * dt;

                if (map.wallActive) {
                    if (CheckCollisionRecs(helena->rect, map.breakableWall)) {
                        if (helena->velocity.x > 0) {
                            helena->rect.x = map.breakableWall.x - helena->rect.width;
                        } else if (helena->velocity.x < 0) {
                            helena->rect.x = map.breakableWall.x + map.breakableWall.width;
                        }
                    }
                }

                CheckMapTransition(&map, &helena->rect, enemiesStarted);

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

                for (int i = 0; i < *enemiesStarted; i++) {
                    enemyList[i]->velocity.y += GRAVITY * dt;

                    enemyList[i]->rect.x += enemyList[i]->velocity.x * dt;
                    enemyList[i]->rect.y += enemyList[i]->velocity.y * dt;

                    if (CheckCollisionRecs(enemyList[i]->rect, map.platforms[0])) {
                        enemyList[i]->rect.y = map.platforms[0].y - enemyList[i]->rect.height;
                        enemyList[i]->velocity.y = 0;
                    }

                    for (int j = 0; j < map.platformsCount; j++) {
                        if (CheckCollisionRecs(enemyList[i]->rect, map.platforms[j])) {
                            enemyList[i]->rect.y = map.platforms[j].y - enemyList[i]->rect.height;
                            enemyList[i]->velocity.y = 0;
                        }
                    }
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
                    for (int i = 0; i < *enemiesStarted; i++) {
                        StartPlayerAttack(helena, enemyList[i], &map);
                    }
                    helena->currentFrame = 0;
                    helena->frameTimer = 0.0f;
                    helena->currentTexture = helena->attackTextures[0];
                }

                if (CanConcludeAttack(helena, timer)) {
                    ConcludePlayerAttack(helena);
                    helena->currentTexture = helena->idleTexture;
                }

                for (int i = 0; i < *enemiesStarted; i++) {
                    enemyList[i]->velocity.x = 0;
                    if (enemyList[i]->active == true) {
                        EnemyVision(enemyList[i], helena);
                    }

                    if (CanEnemyConcludeAttack(enemyList[i], timer)) {
                        ConcludeEnemyAttack(enemyList[i]);
                    }
                }
                
                UpdateCameraToFollowPlayer(&camera, (Vector2){helena->rect.x, helena->rect.y}, SCREEN_WIDTH, SCREEN_HEIGHT, MAP_WIDTH, MAP_HEIGHT);

                if (IsKeyPressed(KEY_M)) currentScreen = MENU;
                
                break;

                default: break;
        }

        BeginDrawing();
        if (currentScreen == GAMEPLAY || currentScreen == INTRO) {
             ClearBackground(BLACK);
        } else {
            ClearBackground(menu.colorBgDark);
        }

        switch(currentScreen) 
        {
            case INTRO:
                {
                    float currentPhaseTime = 0.0f;

                    if (introPhase == 0) {
                        currentPhaseTime = 3.0f;
                        const char* textoTitulo = "METROID LEVELING";
                        const char* textoDemo = "- DEMO -";
                        
                        int w1 = MeasureText(textoTitulo, 50);
                        int w2 = MeasureText(textoDemo, 20);
                        
                        DrawText(textoTitulo, SCREEN_WIDTH/2 - w1/2, SCREEN_HEIGHT/2 - 50, 50, (Color){0, 225, 255, 255}); 
                        DrawText(textoDemo, SCREEN_WIDTH/2 - w2/2, SCREEN_HEIGHT/2 + 10, 20, GRAY);
                    }
                    else if (introPhase == 1) {
                        currentPhaseTime = 7.0f;
                        DrawTexturePro(introImg1, 
                            (Rectangle){0, 0, (float)introImg1.width, (float)introImg1.height},
                            (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT},
                            (Vector2){0,0}, 0.0f, WHITE);
                        
                        DrawRectangle(0, SCREEN_HEIGHT - 120, SCREEN_WIDTH, 120, Fade(BLACK, 0.7f));

                        const char* linha1 = "Há 21 anos, portais surgiram e se abriram nos céus...";
                        const char* linha2 = "Monstros desceram, causando caos, destruição e muitas mortes.";

                        int cx = SCREEN_WIDTH/2;
                        DrawText(linha1, cx - MeasureText(linha1, 20)/2, SCREEN_HEIGHT - 90, 20, WHITE);
                        DrawText(linha2, cx - MeasureText(linha2, 20)/2, SCREEN_HEIGHT - 60, 20, WHITE);
                    }
                    else if (introPhase == 2) {
                        currentPhaseTime = 9.0f;
                        DrawTexturePro(introImg2, 
                            (Rectangle){0, 0, (float)introImg2.width, (float)introImg2.height},
                            (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT},
                            (Vector2){0,0}, 0.0f, WHITE);
                        
                        DrawRectangle(0, SCREEN_HEIGHT - 140, SCREEN_WIDTH, 140, Fade(BLACK, 0.8f));

                        const char* l1 = "Nesse dia, Helena tinha acabado de nascer, mas algo terrível aconteceu...";
                        const char* l2 = "Um dos monstros entrou no hospital e matou várias pessoas,";
                        const char* l3 = "incluindo os pais dela.";

                        int cx = SCREEN_WIDTH/2;
                        DrawText(l1, cx - MeasureText(l1, 20)/2, SCREEN_HEIGHT - 110, 20, WHITE);
                        DrawText(l2, cx - MeasureText(l2, 20)/2, SCREEN_HEIGHT - 80, 20, WHITE);
                        DrawText(l3, cx - MeasureText(l3, 20)/2, SCREEN_HEIGHT - 50, 20, WHITE);
                    }
                    else if (introPhase == 3) {
                        currentPhaseTime = 9.0f;
                        DrawTexturePro(introImg3, 
                            (Rectangle){0, 0, (float)introImg3.width, (float)introImg3.height},
                            (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT},
                            (Vector2){0,0}, 0.0f, WHITE);
                        
                        DrawRectangle(0, SCREEN_HEIGHT - 120, SCREEN_WIDTH, 120, Fade(BLACK, 0.8f));

                        const char* l1 = "Porém, nesse mesmo dia, pessoas com super poderes apareceram";
                        const char* l2 = "e começaram a acabar com os monstros.";

                        int cx = SCREEN_WIDTH/2;
                        DrawText(l1, cx - MeasureText(l1, 20)/2, SCREEN_HEIGHT - 80, 20, WHITE);
                        DrawText(l2, cx - MeasureText(l2, 20)/2, SCREEN_HEIGHT - 50, 20, WHITE);
                    }
                    else if (introPhase == 4) {
                        currentPhaseTime = 12.0f;
                        DrawTexturePro(introImg4, 
                            (Rectangle){0, 0, (float)introImg4.width, (float)introImg4.height},
                            (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT},
                            (Vector2){0,0}, 0.0f, WHITE);
                        
                        DrawRectangle(0, SCREEN_HEIGHT - 160, SCREEN_WIDTH, 160, Fade(BLACK, 0.8f));

                        const char* l1 = "Helena cresceu num orfanato com muitas outras crianças e adolescentes";
                        const char* l2 = "que também perderam seus pais naquele desastre.";
                        const char* l3 = "Helena, no entanto, não superou a dor e estava determinada a investigar";
                        const char* l4 = "a origem dos portais. Ela queria descobrir a verdade e vingança...";

                        int cx = SCREEN_WIDTH/2;
                        DrawText(l1, cx - MeasureText(l1, 20)/2, SCREEN_HEIGHT - 130, 20, WHITE);
                        DrawText(l2, cx - MeasureText(l2, 20)/2, SCREEN_HEIGHT - 100, 20, WHITE);
                        DrawText(l3, cx - MeasureText(l3, 20)/2, SCREEN_HEIGHT - 70, 20, WHITE);
                        DrawText(l4, cx - MeasureText(l4, 20)/2, SCREEN_HEIGHT - 40, 20, WHITE);
                    }
                    else if (introPhase == 5) {
                        currentPhaseTime = 16.0f;
                        DrawTexturePro(introImg5, 
                            (Rectangle){0, 0, (float)introImg5.width, (float)introImg5.height},
                            (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT},
                            (Vector2){0,0}, 0.0f, WHITE);
                        
                        DrawRectangle(0, SCREEN_HEIGHT - 210, SCREEN_WIDTH, 210, Fade(BLACK, 0.8f));

                        const char* l1 = "Helena, agora com 21 anos, decidiu entrar num portal por conta própria,";
                        const char* l2 = "mesmo sabendo ser perigoso para ela que não tinha poderes,";
                        const char* l3 = "mesmo sabendo que o governo avisava sempre para alertar as autoridades";
                        const char* l4 = "se qualquer pessoa avistasse o surgimento de um novo portal.";
                        const char* l5 = "Helena ignorou tudo isso, pegou uma faca, sua mochila e entrou sozinha...";
                        const char* l6 = "E É AQUI QUE NOSSA HISTÓRIA COMEÇA.";

                        int cx = SCREEN_WIDTH/2;
                        int yBase = SCREEN_HEIGHT - 180;
                        int spacing = 30;
                        
                        DrawText(l1, cx - MeasureText(l1, 20)/2, yBase, 20, WHITE);
                        DrawText(l2, cx - MeasureText(l2, 20)/2, yBase + spacing, 20, WHITE);
                        DrawText(l3, cx - MeasureText(l3, 20)/2, yBase + spacing*2, 20, WHITE);
                        DrawText(l4, cx - MeasureText(l4, 20)/2, yBase + spacing*3, 20, WHITE);
                        DrawText(l5, cx - MeasureText(l5, 20)/2, yBase + spacing*4, 20, WHITE);
                        DrawText(l6, cx - MeasureText(l6, 20)/2, yBase + spacing*5, 20, (Color){0, 225, 255, 255});
                    }

                    float fadeAlpha = 0.0f;
                    float fadeDuration = 1.0f;

                    if (introTimer < fadeDuration) {
                        fadeAlpha = 1.0f - (introTimer / fadeDuration);
                    }
                    else if (introTimer > currentPhaseTime - fadeDuration) {
                        fadeAlpha = (introTimer - (currentPhaseTime - fadeDuration)) / fadeDuration;
                    }

                    if (fadeAlpha < 0.0f) fadeAlpha = 0.0f;
                    if (fadeAlpha > 1.0f) fadeAlpha = 1.0f;

                    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, fadeAlpha));

                    if ((int)(GetTime() * 2) % 2 == 0) {
                        DrawText("[ENTER] PULAR", SCREEN_WIDTH - 150, SCREEN_HEIGHT - 20, 10, WHITE);
                    }
                }
                break;

            case MENU:
            case CREDITS:
                DrawMenu(&menu, currentScreen);
                break;

            case LEADERBOARD:
                DrawMenu(&menu, currentScreen); 

                    if (!rankingCarregado) {

                    if (listaScores != NULL) LiberarLista(listaScores);
                    
                    listaScores = CarregarListaScores();
                    rankingCarregado = true;
                }


                if (listaScores == NULL) {
                    DrawText("Nenhum registro encontrado.", 350, 250, 20, GRAY);
                } else {
                    ScoreNode *aux = listaScores;
                    int i = 0;

                    while (aux != NULL && i < 5) {
                        char tempoTexto[20];
                        FormatarTempo(aux->tempo, tempoTexto);

                        char linha[100];
                        sprintf(linha, "%d. %s .  .  .  .  .  .  .  . %s", i+1, aux->nome, tempoTexto);
                          
                        DrawText(linha, 320, 180 + (i * 40), 20, menu.colorText);

                        aux = aux->next;
                        i++;
                    }
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

                Rectangle rectsource = {0.0f, 0.0f, (float) helena->currentTexture.width, (float) helena->currentTexture.height};
                // Para virar a texture para o lado esquerdo
                if (helena->facing == 1) {
                    rectsource.width = -rectsource.width;
                }
                if (helena->attacking && !rectChangeToAttack) {
                    helena->rect.width = (float) helena->currentTexture.width * 0.2;
                    helena->rect.height = (float) helena->currentTexture.height * 0.2;
                    rectChangeToAttack = true;
                }
                else if (!helena->attacking && rectChangeToAttack) {
                    helena->rect.y = helena->rect.y + 5;
                    helena->rect.width = (float) helena->currentTexture.width * 0.2;
                    helena->rect.height = (float) helena->currentTexture.height * 0.2;
                    rectChangeToAttack = false;
                }
                Rectangle rectdest = helena->rect;
                
                Rectangle rectsource_e[9]; // *enemiesStarted
                Rectangle rectdest_e[9]; // *enemiesStarted
                for (int i = 0; i < *enemiesStarted; i++) {
                    rectsource_e[i] = (Rectangle) {0.0f, 0.0f, (float) enemyList[i]->currentTexture.width, (float) enemyList[i]->currentTexture.height};
                    if (enemyList[i]->facing == 1) {
                        rectsource_e[i].width = -rectsource_e[i].width;
                    }
                    rectdest_e[i] = enemyList[i]->rect;
                }
                
                DrawMapBackground(&map);

                BeginMode2D(camera);

                    DrawMapPlatforms(&map);


                    for (int i = 0; i < *enemiesStarted; i++) {
                        if (enemyList[i]->active == true) {
                            DrawRectangleRec(enemyList[i]->vision, GRAY);
                            DrawTexturePro(
                                enemyList[i]->currentTexture,
                                rectsource_e[i],
                                rectdest_e[i],
                                (Vector2){0, 0},
                                0.0f,
                                WHITE
                            );
                            DrawRectangleRec(enemyList[i]->hitbox, RED);
                            if (enemyList[i]->delayAttack != 0)
                                DrawText("delay", enemyList[i]->rect.x, enemyList[i]->rect.y, 10, RED);
                        }
                    }

                    if (helena->active == true) {
                        DrawTexturePro(
                            helena->currentTexture,
                            rectsource,
                            rectdest, 
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

    UnloadTexture(introImg1);
    UnloadTexture(introImg2);
    UnloadTexture(introImg3);
    UnloadTexture(introImg4); 
    UnloadTexture(introImg5);
    
    UnloadMusicStream(musicMenu);
    UnloadMusicStream(musicGame);
    CloseAudioDevice();

    UnloadTexture(texPlayerIdle);
    UnloadTexture(texPlayerRun0);
    UnloadTexture(texPlayerRun1);
    UnloadTexture(texPlayerRun2);
    UnloadTexture(texPlayerRun3);
    UnloadTexture(texPlayerAttack0);
    UnloadTexture(texPlayerAttack1);
    UnloadTexture(texPlayerAttack2);
    UnloadTexture(texPlayerJump0);
    UnloadTexture(texPlayerJump1);
    UnloadTexture(texPlayerJump2);

    UnloadTexture(texEnemyIdle);
    UnloadTexture(texEnemyRun0);
    UnloadTexture(texEnemyRun1);
    UnloadTexture(texEnemyRun2);
    UnloadTexture(texEnemyRun3);
    UnloadTexture(texEnemyAttack0);
    UnloadTexture(texEnemyAttack1);
    UnloadTexture(texEnemyAttack2);

    UnloadTexture(texEnem0);
    UnloadTexture(menuBg);

    UnloadMap(&map);

    free(helena);

    if (enemyList != NULL) {
        for (int i = 0; i < *enemiesStarted; i++) {
            free(enemyList[i]);
        }
        free(enemyList);
    }

    for (int i = 0; i < AMOUNT_AREAS; i++) {
        free(enemiesManager[i]);
    }
    free(enemiesManager);

    free(enemiesStarted);
    
    CloseWindow();
    
    return 0;
}