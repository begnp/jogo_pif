#ifndef ITEM_H
#define ITEM_H

#include "raylib.h"
#include "player.h"

typedef struct Item {
    Rectangle rect;
    Vector2 startPos;
    Texture2D texture;
    bool active;   
    float floatTimer; 
} Item;

void InitItem(Item *item, Texture2D tex, float x, float y);
void UpdateItem(Item *item); 
void DrawItem(Item *item);

#endif