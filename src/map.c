#include "map.h"
#include <stdlib.h>
#include <stdio.h>

void UnloadCurrentPlatforms(Map *map) {
    if (map->platforms != NULL) {
        free(map->platforms);
        map->platforms = NULL;
    }
    map->platformsCount = 0;
}

void LoadArea(Map *map, int areaIndex) {
    UnloadCurrentPlatforms(map);
    map->currentArea = areaIndex;

    switch (areaIndex) {
        case 1:
            map->platformsCount = 4;
            map->platforms = (Rectangle *) malloc(sizeof(Rectangle) * map->platformsCount);

    
            map->platforms[0] = (Rectangle){ -500, 500, 1600, 500 };

            map->platforms[1] = (Rectangle){ -500, -500, 550, 1500 };
 
            map->platforms[2] = (Rectangle){ -500, -330, 1600, 550 };
 
            map->platforms[3] = (Rectangle){ 800, 220, 300, 150 };

            map->breakableWall = (Rectangle){ 0, 0, 0, 0 };
            break;

        case 2: 
            map->platformsCount = 12; 
            map->platforms = (Rectangle *) malloc(sizeof(Rectangle) * map->platformsCount);
            
            map->platforms[0] = (Rectangle){ 0, 550, 400, 50 };  

            map->platforms[1] = (Rectangle){ 600, 550, 400, 50 }; 

            map->platforms[4] = (Rectangle){ 0, -50, 400, 60 };

            map->platforms[5] = (Rectangle){ 600, -50, 400, 60 }; 

            map->platforms[2] = (Rectangle){ 0, 0, 40, 350 }; 

            map->platforms[3] = (Rectangle){ 960, 0, 40, 400 }; 

            map->platforms[6] = (Rectangle){ 350, 440, 300, 20 };

            map->platforms[7] = (Rectangle){ 40, 320, 220, 20 };

            map->platforms[8] = (Rectangle){ 740, 210, 220, 20 };

            map->platforms[9] = (Rectangle){ 350, 110, 300, 20 };

            map->platforms[10] = (Rectangle){ 40, 180, 240, 20 };

            map->platforms[11] = (Rectangle){ 380, 260, 240, 20 };

            map->breakableWall = (Rectangle){ 0, 0, 0, 0 };
            break;

        case 3:
            map->platformsCount = 16; 
            map->platforms = (Rectangle *) malloc(sizeof(Rectangle) * map->platformsCount);

            map->platforms[0] = (Rectangle){ 0, 0, 40, 600 }; 
            map->platforms[1] = (Rectangle){ 960, 0, 40, 600 };  
            map->platforms[2] = (Rectangle){ 0, -50, 400, 60 };   
            map->platforms[3] = (Rectangle){ 600, -50, 400, 60 };

            map->platforms[4] = (Rectangle){ 40, 500, 420, 100 };
            
            map->platforms[5] = (Rectangle){ 340, 400, 180, 20 };

            map->platforms[6] = (Rectangle){ 40, 320, 180, 20 };

            map->platforms[7] = (Rectangle){ 340, 240, 180, 20 };

            map->platforms[8] = (Rectangle){ 40, 160, 180, 20 };

            map->platforms[9] = (Rectangle){ 320, 100, 420, 20 };

            map->platforms[10] = (Rectangle){ 460, 580, 540, 20 };

            map->breakableWall = (Rectangle){ 0, 0, 0, 0 };

            map->platforms[1] = (Rectangle){ 960, -50, 40, 300 };

            map->platforms[10] = (Rectangle){ 960, 370, 40, 230 };

            map->platforms[11] = (Rectangle){ 460, 500, 140, 100 };

            map->platforms[12] = (Rectangle){ 600, 420, 100, 20 };

            map->platforms[13] = (Rectangle){ 700, 340, 100, 20 };

            map->platforms[14] = (Rectangle){ 800, 250, 160, 20 };

            map->platforms[15] = (Rectangle){ 600, 580, 360, 20 };

            map->breakableWall = (Rectangle){ 960, 250, 40, 120 };
            break;
        
        case 4: 
            map->platformsCount = 11; 
            map->platforms = (Rectangle *) malloc(sizeof(Rectangle) * map->platformsCount);
            
            map->platforms[0] = (Rectangle){ 0, 550, 400, 50 };
            map->platforms[1] = (Rectangle){ 600, 550, 400, 50 }; 
            
            map->platforms[2] = (Rectangle){ 0, 0, 40, 600 };   
            map->platforms[3] = (Rectangle){ 960, 0, 40, 600 }; 

            map->platforms[4] = (Rectangle){ 0, -50, 1000, 60 };

            map->platforms[5] = (Rectangle){ 300, 420, 400, 20 }; 
            
            map->platforms[6] = (Rectangle){ 300, 230, 400, 20 };

            map->platforms[7] = (Rectangle){ 40, 350, 160, 20 };

            map->platforms[8] = (Rectangle){ 40, 150, 120, 20 };

            map->platforms[9] = (Rectangle){ 800, 350, 160, 20 };

            map->platforms[10] = (Rectangle){ 840, 150, 120, 20 };

            map->breakableWall = (Rectangle){ 0, 0, 0, 0 };
            break;

        default:
            printf("Erro: Area %d nao existe!\n", areaIndex);
            break;
    }
}

void CheckMapTransition(Map *map, Rectangle *playerRect) {
    
    if (map->currentArea == 1) {
        if (playerRect->x > 980) {
            LoadArea(map, 2);
            playerRect->x = 60;      
            playerRect->y = 550 - playerRect->height;     
        }
    }

    else if (map->currentArea == 2) {

        if (playerRect->x < 10) {
            if (playerRect->y > 350) { 
                LoadArea(map, 1);
                playerRect->x = 950; 
                playerRect->y = 500 - playerRect->height; 
            }
        }

        else if (playerRect->y < -40) {
            if (playerRect->x > 350 && playerRect->x < 650) {
                LoadArea(map, 4);
                playerRect->y = 500;
            }
        }
!
        else if (playerRect->y > 600) {
            LoadArea(map, 3);
            playerRect->y = 0; 
        }
    }

    else if (map->currentArea == 3) {
        if (playerRect->y < -40) {
            if (playerRect->x > 350 && playerRect->x < 650) {
                LoadArea(map, 2);
                playerRect->y = 580; 
            }
        }
    }
    else if (map->currentArea == 4) {
        if (playerRect->y > 600) {
            LoadArea(map, 2);
            playerRect->y = -30; 
        }
    }
}

void InitMap(Map *map) {
    map->texBackground = LoadTexture("assets/1.png");
    map->texForeground = LoadTexture("assets/0.png");
    map->texTile = LoadTexture("assets/CaveTileset.png");

    if (map->texTile.id == 0) printf("Aviso: CaveTileset.png nao encontrado.\n"); 

    map->colorBorder = (Color){ 20, 20, 20, 255 };
    map->wallActive = true;
    map->wallHealth = 3;
    map->platforms = NULL;
    
    LoadArea(map, 1);
}

void DrawMapBackground(Map *map) {
    Rectangle sourceBg = { 0.0f, 0.0f, (float)map->texBackground.width, (float)map->texBackground.height };
    Rectangle destBg = { 0.0f, 0.0f, (float)MAP_WIDTH, (float)MAP_HEIGHT };
    DrawTexturePro(map->texBackground, sourceBg, destBg, (Vector2){0,0}, 0.0f, WHITE);

    if (map->texForeground.id > 0) {
        Rectangle sourceFg = { 0.0f, 0.0f, (float)map->texForeground.width, (float)map->texForeground.height };
        Rectangle destFg = { 0.0f, 0.0f, (float)MAP_WIDTH, (float)MAP_HEIGHT };
        DrawTexturePro(map->texForeground, sourceFg, destFg, (Vector2){0,0}, 0.0f, WHITE);
    }
}

void DrawTileRect(Texture2D texture, Rectangle dest, Rectangle source) {
    DrawTexturePro(texture, source, dest, (Vector2){0,0}, 0.0f, WHITE);
}

void DrawMapPlatforms(Map *map) {
    float tileSize = 32.0f;

    for (int i = 0; i < map->platformsCount; i++) {
        Rectangle plat = map->platforms[i];

        if (map->texTile.id > 0) {
            if (plat.height > 40) {
                for (float x = 0; x < plat.width; x += tileSize) {
                    for (float y = 0; y < plat.height; y += tileSize) {
                        float drawWidth = (x + tileSize > plat.width) ? (plat.width - x) : tileSize;
                        float drawHeight = (y + tileSize > plat.height) ? (plat.height - y) : tileSize;
                        Rectangle source = { 32.0f, 96.0f, drawWidth, drawHeight };
                        if (i == 0 && y == 0) source.y = 64.0f; 
                        Rectangle dest = { plat.x + x, plat.y + y, drawWidth, drawHeight };
                        DrawTileRect(map->texTile, dest, source);
                    }
                }
                if (i == 0) {
                    DrawRectangleGradientV((int)plat.x, (int)(plat.y + 30), (int)plat.width, (int)(plat.height - 30), (Color){0,0,0,0}, (Color){0,0,0,150});
                }
            }
            else {
                for (float x = 0; x < plat.width; x += tileSize) {
                    float drawWidth = (x + tileSize > plat.width) ? (plat.width - x) : tileSize;
                    Rectangle source = { 32.0f, 0.0f, drawWidth, 32.0f };
                    Rectangle dest = { plat.x + x, plat.y, drawWidth, plat.height };
                    DrawTileRect(map->texTile, dest, source);
                }
            }
        } else {
            DrawRectangleRec(plat, DARKGRAY);
        }
    }
}

void DrawMapForeground(Map *map) {
    if (map->currentArea == 1) {
        DrawRectangleGradientH(800, 370, 300, 130, (Color){0,0,0,0}, BLACK);
    }
    else if (map->currentArea == 2) {
        DrawRectangleGradientV(400, -70, 200, 100, BLACK, (Color){0,0,0,0});
        DrawRectangleGradientV(400, 540, 200, 100, (Color){0,0,0,0}, BLACK);
    }
}

void UnloadMap(Map *map) {
    UnloadTexture(map->texBackground);
    UnloadTexture(map->texForeground);
    UnloadTexture(map->texTile); 
    UnloadCurrentPlatforms(map);
}