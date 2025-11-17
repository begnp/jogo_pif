#include "menu.h"
#include <stdio.h>

void InitMenu(Menu *menu, int screenWidth, int screenHeight, Texture2D bgTexture) {
    menu->background = bgTexture;

    menu->colorBgDark = (Color){ 10, 10, 15, 255 }; 
    menu->colorAccent = (Color){ 0, 225, 255, 255 };    
    menu->colorText   = (Color){ 240, 240, 240, 255 }; 

    
    float buttonWidth = 300;
    float buttonHeight = 50;
    float centerX = screenWidth / 2.0f - buttonWidth / 2.0f;
    float startY = 320;
    float spacing = 70;

    menu->btnPlay        = (Rectangle){ centerX, startY, buttonWidth, buttonHeight };
    menu->btnLeaderboard = (Rectangle){ centerX, startY + spacing, buttonWidth, buttonHeight };
    menu->btnCredits     = (Rectangle){ centerX, startY + spacing * 2, buttonWidth, buttonHeight };

    menu->btnBack = (Rectangle){ 50, screenHeight - 80, 150, 40 };
}

GameScreen UpdateMenu(Menu *menu, GameScreen currentScreen) {
    Vector2 mousePoint = GetMousePosition();
    bool clicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    if (currentScreen == MENU) {
        if (CheckCollisionPointRec(mousePoint, menu->btnPlay) && clicked) return GAMEPLAY;
        if (CheckCollisionPointRec(mousePoint, menu->btnLeaderboard) && clicked) return LEADERBOARD;
        if (CheckCollisionPointRec(mousePoint, menu->btnCredits) && clicked) return CREDITS;
    }
    else if (currentScreen == LEADERBOARD || currentScreen == CREDITS) {
        if (CheckCollisionPointRec(mousePoint, menu->btnBack) && clicked) return MENU;
    }

    return currentScreen;
}

void DrawSystemButton(Menu *menu, Rectangle rect, const char* text, Vector2 mousePoint) {
    bool isHover = CheckCollisionPointRec(mousePoint, rect);

    if (isHover) {
    
        DrawRectangleRec(rect, menu->colorAccent);
        
        DrawRectangleLinesEx((Rectangle){rect.x-2, rect.y-2, rect.width+4, rect.height+4}, 2, Fade(menu->colorAccent, 0.3f));
        
        int textWidth = MeasureText(text, 20);
        DrawText(text, rect.x + (rect.width/2 - textWidth/2), rect.y + 15, 20, BLACK);
    } else {
    
        DrawRectangleLinesEx(rect, 1, menu->colorAccent);
        
        DrawRectangleRec(rect, Fade(BLACK, 0.5f));

        int textWidth = MeasureText(text, 20);
        DrawText(text, rect.x + (rect.width/2 - textWidth/2), rect.y + 15, 20, menu->colorAccent);
    }
}

void DrawMenu(Menu *menu, GameScreen currentScreen) {
    Vector2 mousePoint = GetMousePosition();
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    ClearBackground(menu->colorBgDark);
    
    if (menu->background.id > 0) {
        DrawTexturePro(menu->background, 
            (Rectangle){0,0, menu->background.width, menu->background.height}, 
            (Rectangle){0,0, screenW, screenH}, 
            (Vector2){0,0}, 0.0f, Fade(WHITE, 0.2f));
    }

    for (int i = 0; i < screenW; i += 40) DrawLine(i, 0, i, screenH, Fade(menu->colorAccent, 0.05f));
    for (int i = 0; i < screenH; i += 40) DrawLine(0, i, screenW, i, Fade(menu->colorAccent, 0.05f));

    if (currentScreen == MENU) {
    
        const char* title = "Metroid Leveling"; 
        const char* subtitle = "INICIANDO SISTEMA...";
        
        int titleW = MeasureText(title, 60);
        int subW = MeasureText(subtitle, 20);

        
        DrawText(title, screenW/2 - titleW/2 + 4, 120 + 4, 60, BLACK);
    
        DrawText(title, screenW/2 - titleW/2, 120, 60, menu->colorAccent);
        
        DrawText(subtitle, screenW/2 - subW/2, 190, 20, menu->colorText);
        DrawLine(screenW/2 - 150, 220, screenW/2 + 150, 220, menu->colorAccent); 

        DrawSystemButton(menu, menu->btnPlay, "[ JOGAR ]", mousePoint);
        DrawSystemButton(menu, menu->btnLeaderboard, "[ RANKING ]", mousePoint);
        DrawSystemButton(menu, menu->btnCredits, "[ CREDITOS ]", mousePoint);
        
        DrawText("v1.0.0 // PLAYER_ID: #001", 10, screenH - 20, 10, Fade(menu->colorAccent, 0.5f));
    }
    else if (currentScreen == LEADERBOARD) {
        DrawText("[ RANKING DE CAÇADORES ]", 350, 100, 30, menu->colorAccent);
        DrawRectangleLines(300, 150, 680, 300, Fade(menu->colorAccent, 0.3f));
        
        DrawText("1. JIN-WOO  -  00:45s", 320, 170, 20, menu->colorText);
        DrawText("2. HELENA   -  01:12s", 320, 200, 20, WHITE);
        
        DrawSystemButton(menu, menu->btnBack, "< VOLTAR", mousePoint);
    }
    else if (currentScreen == CREDITS) {
        DrawText("[ DESENVOLVEDORES ]", 400, 100, 30, menu->colorAccent);
        
        DrawText("Código & Arte:", 400, 200, 20, menu->colorAccent);
        DrawText("Arthur Reis", 400, 230, 20, WHITE);
        DrawText("Bernardo Guimarães", 400, 260, 20, WHITE);
        DrawText("Cauã Henrique", 400, 290, 20, WHITE);
        
        DrawSystemButton(menu, menu->btnBack, "< VOLTAR", mousePoint);
    }
}