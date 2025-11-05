#include "camera.h"
#include "player.h"
#include "raylib.h"
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

#define PLAYER_JUMP_SPEED -350.0f
#define PLAYER_HOR_SPEED 200.0f
#define GRAVITY 500.0f

int main(void) {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Conceito 1: Saltador Quadrado");	


    Player player = {0};
    player.rect.x = SCREEN_WIDTH / 2.0f;
    player.rect.y = SCREEN_HEIGHT - 100.0f;
    player.rect.width = 40;
    player.rect.height = 0;
    player.velocity = (Vector2){0, 0};
    player.canJump = false;
	player.texture = LoadTexture("./assets/Ellie_f0.png");
	
	Rectangle floor = {0, SCREEN_HEIGHT - 20, SCREEN_WIDTH, 20};
    
    Rectangle platforms[] = {
        {100, 300, 200, 20},
        {400, 200, 150, 20},
        {500, 100, 100, 20}
    };
    int numPlatforms = sizeof(platforms) / sizeof(platforms[0]);
	
	SetTargetFPS(60);

	Camera2D camera = InitCamera((Vector2){player.rect.x, player.rect.y}, (Vector2){400, 225});
	
	while(!WindowShouldClose()) {
		float dt = GetFrameTime();
		
		player.velocity.x = 0;
		
		if (IsKeyDown(KEY_RIGHT)) {
			player.velocity.x = PLAYER_HOR_SPEED;
		}
		if (IsKeyDown(KEY_LEFT)) {
			player.velocity.x = -PLAYER_HOR_SPEED;
		}
		
		if (IsKeyPressed(KEY_SPACE) && player.canJump) {
			player.velocity.y = PLAYER_JUMP_SPEED;
			player.canJump = false;
		}
		
		player.velocity.y += GRAVITY * dt;
		
		player.rect.x += player.velocity.x * dt;
		player.rect.y += player.velocity.y * dt;
		
		if (CheckCollisionRecs(player.rect, floor)) {
			player.rect.y = floor.y - player.rect.height;
			player.velocity.y = 0;
			player.canJump = true;
		}
		
		
		
		for (int i = 0; i < numPlatforms; i++) {
			if (CheckCollisionRecs(player.rect, platforms[i])) {
				if (player.velocity.y > 0) {
					player.rect.y = platforms[i].y - player.rect.height;
					player.velocity.y = 0;
					player.canJump = true;
				}
			}
		}
		
		UpdateCameraToFollowPlayer(&camera, (Vector2){player.rect.x, player.rect.y}, SCREEN_WIDTH, SCREEN_HEIGHT);
		
		BeginDrawing();
		ClearBackground(SKYBLUE);
		BeginMode2D(camera);

			
			//DrawTexture(snorlax, player.rect.x, player.rect.y, WHITE);
			
			DrawRectangleRec(player.rect, WHITE);
			DrawTextureEx(player.texture, (Vector2){player.rect.x, player.rect.y - 50}, 0.0f, 0.25f, WHITE);
			
			DrawRectangleRec(floor, GREEN);
			
			for (int i = 0; i < numPlatforms; i++) {
				DrawRectangleRec(platforms[i], GRAY);
			}
			
		EndDrawing();
		
	}

    UnloadTexture(player.texture);
	
	CloseWindow();
    
    return 0;
}


















