#include "map.h"
#include <stdlib.h>

void InitMap(Map *map) {

    map->platformsCount = 5;
    
    map->platforms = (Rectangle *) malloc(sizeof(Rectangle) * map->platformsCount);
    
    map->color = GRAY;

    map->platforms[0] = (Rectangle){0, 450, 1000, 40}; 
    
    map->platforms[1] = (Rectangle){300, 350, 100, 20};
    
    map->platforms[2] = (Rectangle){100, 300, 200, 20};
    
    map->platforms[3] = (Rectangle){400, 200, 150, 20};
    
    map->platforms[4] = (Rectangle){500, 100, 100, 20};
}

void DrawMap(Map *map) {
    for (int i = 0; i < map->platformsCount; i++) {
        DrawRectangleRec(map->platforms[i], map->color);
        DrawRectangleLinesEx(map->platforms[i], 1, DARKGRAY);
    }
}

void UnloadMap(Map *map) {
    if (map->platforms != NULL) {
        free(map->platforms);
        map->platforms = NULL;
    }
}