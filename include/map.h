#ifndef MAP_H
#define MAP_H

#include "raylib.h"

typedef struct Map {
    Rectangle *platforms;
    int platformsCount;
    Color color;         
} Map;

void InitMap(Map *map);

void DrawMap(Map *map);

void UnloadMap(Map *map);

#endif