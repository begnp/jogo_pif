#ifndef MAP_H
#define MAP_H

#include "raylib.h"

#define MAP_WIDTH 1000
#define MAP_HEIGHT 600

typedef struct Map {
    Rectangle *platforms; 
    int platformsCount;

    Texture2D texBackground;
    Texture2D texForeground;
    Texture2D texTile;
           
    Color colorFillTop;
    Color colorFillBot;
    Color colorBorder;

    int currentArea;

    Rectangle breakableWall;
    bool wallActive;
    int wallHealth;  
} Map;

void InitMap(Map *map);
void LoadArea(Map *map, int areaIndex);
void DrawMapBackground(Map *map);
void DrawMapPlatforms(Map *map);
void UnloadMap(Map *map);

#endif