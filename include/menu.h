#ifndef MENU_H
#define MENU_H

#include "raylib.h"

typedef enum GameScreen { 
    LOGO = 0, 
    MENU, 
    GAMEPLAY, 
    LEADERBOARD, 
    CREDITS,
    EXIT 
} GameScreen;

typedef struct Menu {
    Texture2D background;
    
    Rectangle btnPlay;
    Rectangle btnLeaderboard;
    Rectangle btnCredits;
    Rectangle btnBack;
    Rectangle btnExit;

    Color colorBgDark;      
    Color colorAccent;      
    Color colorText;        
    
} Menu;

void InitMenu(Menu *menu, int screenWidth, int screenHeight, Texture2D bgTexture);
GameScreen UpdateMenu(Menu *menu, GameScreen currentScreen);
void DrawMenu(Menu *menu, GameScreen currentScreen);

#endif