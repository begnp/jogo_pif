#include "item.h"
#include <math.h> 

void InitItem(Item *item, Texture2D tex, float x, float y) {
    item->texture = tex;
    item->rect.x = x;
    item->rect.y = y;
    item->rect.width = tex.width; 
    item->rect.height = tex.height;
    
    item->startPos = (Vector2){ x, y };
    item->active = true;
    item->floatTimer = 0.0f;
}

void UpdateItem(Item *item) {
    if (!item->active) return;
    item->floatTimer += GetFrameTime();
    item->rect.y = item->startPos.y + sinf(item->floatTimer * 3.0f) * 10.0f;
}

void DrawItem(Item *item) {
    if (item->active) {
        DrawTexture(item->texture, (int)item->rect.x, (int)item->rect.y, WHITE);
        DrawCircleGradient((int)(item->rect.x + item->rect.width/2), 
                           (int)(item->rect.y + item->rect.height/2), 
                           20, Fade(WHITE, 0.3f), Fade(WHITE, 0.0f));
    }
}