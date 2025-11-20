#include "map.h"
#include <stdlib.h>
#include <stdio.h>

void InitMap(Map *map) {
    map->platformsCount = 5;
    map->platforms = (Rectangle *) malloc(sizeof(Rectangle) * map->platformsCount);

    map->texBackground = LoadTexture("assets/1.png");
    map->texForeground = LoadTexture("assets/0.png");
    
    map->texTile = LoadTexture("assets/CaveTileset.png");

    if (map->texTile.id == 0) printf("Aviso: CaveTileset.png nao encontrado.\n"); 

    map->colorBorder = (Color){ 20, 20, 20, 255 };

    map->platforms[0] = (Rectangle){0, 520, 1000, 80};  
    map->platforms[1] = (Rectangle){300, 400, 100, 20};
    map->platforms[2] = (Rectangle){100, 300, 200, 20};
    map->platforms[3] = (Rectangle){450, 250, 150, 20};
    map->platforms[4] = (Rectangle){650, 150, 100, 20};
}

void DrawMapBackground(Map *map) {
    Rectangle sourceBg = { 0.0f, 0.0f, (float)map->texBackground.width, (float)map->texBackground.height };
    Rectangle destBg = { 0.0f, 0.0f, (float)MAP_WIDTH, (float)MAP_HEIGHT };
    DrawTexturePro(map->texBackground, sourceBg, destBg, (Vector2){0,0}, 0.0f, WHITE);

    Rectangle sourceFg = { 0.0f, 0.0f, (float)map->texForeground.width, (float)map->texForeground.height };
    Rectangle destFg = { 0.0f, 0.0f, (float)MAP_WIDTH, (float)MAP_HEIGHT };
    DrawTexturePro(map->texForeground, sourceFg, destFg, (Vector2){0,0}, 0.0f, WHITE);
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
                        DrawTexturePro(map->texTile, source, dest, (Vector2){0,0}, 0.0f, WHITE);
                    }
                }

                float fadeStart = 30.0f; 
                
                DrawRectangleGradientV(
                    (int)plat.x, 
                    (int)(plat.y + fadeStart), 
                    (int)plat.width, 
                    (int)(plat.height - fadeStart), 
                    (Color){ 0, 0, 0, 0 },
                    (Color){ 0, 0, 0, 255 } 
                );
                
            }
            else {
                for (float x = 0; x < plat.width; x += tileSize) {
                    float drawWidth = (x + tileSize > plat.width) ? (plat.width - x) : tileSize;
                    Rectangle source = { 32.0f, 0.0f, drawWidth, 32.0f };
                    Rectangle dest = { plat.x + x, plat.y, drawWidth, plat.height };
                    DrawTexturePro(map->texTile, source, dest, (Vector2){0,0}, 0.0f, WHITE);
                }
            }
            
        } 
        else {
            DrawRectangleRec(plat, DARKGRAY);
        }
    }
}

void UnloadMap(Map *map) {
    UnloadTexture(map->texBackground);
    UnloadTexture(map->texForeground);
    UnloadTexture(map->texTile); 

    if (map->platforms != NULL) {
        free(map->platforms);
        map->platforms = NULL;
    }
}