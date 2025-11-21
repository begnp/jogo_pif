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
            map->platformsCount = 8;
            map->platforms = (Rectangle *) malloc(sizeof(Rectangle) * map->platformsCount);

            map->platforms[0] = (Rectangle){-150, 520, 1500, 150};
            map->platforms[1] = (Rectangle){1450, 620, 350, 20};  
            
            map->platforms[2] = (Rectangle){1900, 520, 150, 150};
            map->platforms[3] = (Rectangle){2050, 400, 150, 250}; 
            map->platforms[4] = (Rectangle){2200, 520, 150, 40}; 
            
            map->platforms[5] = (Rectangle){1450, 420, 90, 20};
            map->platforms[6] = (Rectangle){1740, 350, 240, 20}; 
            map->platforms[7] = (Rectangle){2100, 250, 200, 30};   

            if (map->wallActive) {
                map->breakableWall = (Rectangle){ 1350, 420, 100, 220 };
            } else {
                map->breakableWall = (Rectangle){ 0, 0, 0, 0 };
            }
            break;

        case 2:
            map->platformsCount = 3;
            map->platforms = (Rectangle *) malloc(sizeof(Rectangle) * map->platformsCount);
            map->platforms[0] = (Rectangle){0, 500, 1000, 100};
            map->platforms[1] = (Rectangle){300, 400, 200, 20};
            map->platforms[2] = (Rectangle){600, 300, 200, 20};
            break;

        default:
            printf("Erro: Area %d nao existe!\n", areaIndex);
            break;
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

    Rectangle sourceFg = { 0.0f, 0.0f, (float)map->texForeground.width, (float)map->texForeground.height };
    Rectangle destFg = { 0.0f, 0.0f, (float)MAP_WIDTH, (float)MAP_HEIGHT };
    DrawTexturePro(map->texForeground, sourceFg, destFg, (Vector2){0,0}, 0.0f, WHITE);
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

                        if (y == 0) source.y = 64.0f; 

                        Rectangle dest = { plat.x + x, plat.y + y, drawWidth, drawHeight };
                        DrawTileRect(map->texTile, dest, source);
                    }
                }
                DrawRectangleGradientV((int)plat.x, (int)(plat.y + 30), (int)plat.width, (int)(plat.height - 30), (Color){0,0,0,0}, (Color){0,0,0,255});
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

    if (map->wallActive) {
        Rectangle wall = map->breakableWall;
        
        if (map->texTile.id > 0) {
            for (float x = 0; x < wall.width; x += tileSize) {
                for (float y = 0; y < wall.height; y += tileSize) {
                    float drawWidth = (x + tileSize > wall.width) ? (wall.width - x) : tileSize;
                    float drawHeight = (y + tileSize > wall.height) ? (wall.height - y) : tileSize;

                    Rectangle source = { 32.0f, 96.0f, drawWidth, drawHeight }; 
                    Rectangle dest = { wall.x + x, wall.y + y, drawWidth, drawHeight };
                    
                    DrawTexturePro(map->texTile, source, dest, (Vector2){0,0}, 0.0f, LIGHTGRAY);
                    
                    DrawRectangleLinesEx(dest, 1, (Color){0,0,0,50});
                }
            }
        } else {
            DrawRectangleRec(wall, BROWN);
        }
    }
}

void UnloadMap(Map *map) {
    UnloadTexture(map->texBackground);
    UnloadTexture(map->texForeground);
    UnloadTexture(map->texTile); 
    UnloadCurrentPlatforms(map);
}