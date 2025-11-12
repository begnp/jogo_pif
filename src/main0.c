#include "camera.h"
#include "enemy.h"
#include "player.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600

#define PLAYER_JUMP_SPEED -350.0f
#define PLAYER_HOR_SPEED 200.0f
#define GRAVITY 500.0f

int main(void) {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Conceito 1: Saltador Quadrado");


	Image r0 = LoadImage("./assets/Ellie_f0_right.png");
	Image r1 = LoadImage("./assets/Ellie_f0_left.png");
	
	Image r0_a = LoadImage("./assets/Ellie_f_a_right.png");
	Image r1_a = LoadImage("./assets/Ellie_f_a_left.png");
    
	Texture2D texRight = LoadTextureFromImage(r0);
	Texture2D texLeft = LoadTextureFromImage(r1);
	Texture2D texAttackRight = LoadTextureFromImage(r0_a);
	Texture2D texAttackLeft = LoadTextureFromImage(r1_a);

	UnloadImage(r0);
	UnloadImage(r1);
	UnloadImage(r0_a);
	UnloadImage(r1_a); 

	Player *helena = (Player *) malloc(sizeof(Player));
	
	*helena = InitPlayer(helena, texRight);
	// Enemy *enemy = ;
	// InitEnemy();

	// helena->texture = texRight; //textura inicial
	// helena->position.x = SCREEN_WIDTH / 2.0f;
    // helena->position.y = 375.0f;
    // helena->rect.x = helena->position.x;
    // helena->rect.y = helena->position.y;
    // helena->rect.width = (float) helena->texture.width * 0.2;
    // helena->rect.height = (float) helena->texture.height * 0.2;
    // helena->velocity = (Vector2){0, 0};
    // helena->canJump = false;
	// helena->attacking = false;
	// helena->facing = 0;

	float a_timer = 0;
	
	Rectangle floor = {0, 450, SCREEN_WIDTH, 20};
    
    Rectangle platforms[] = {
		{300, 350, 100, 20},
        {100, 300, 200, 20},
        {400, 200, 150, 20},
        {500, 100, 100, 20}
    };
    int numPlatforms = sizeof(platforms) / sizeof(platforms[0]);
	
	SetTargetFPS(60);

	Camera2D camera = InitCamera((Vector2){helena->rect.x, helena->rect.y}, (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});
	
	while(!WindowShouldClose()) {

		double timer = GetTime();

		float dt = GetFrameTime();

		// printf("%f\n\n", timer);

		if (helena->attacking == true && (timer > a_timer + 0.5)) {
			helena->attacking = false;
			if (helena->facing == 0) {
				helena->texture = texRight;
			}
			else if (helena->facing == 1) {
				helena->texture = texLeft;
			}
		}

		/* if (IsKeyPressed(KEY_F11)) {
			ToggleFullscreen();
		} */
		
		helena->velocity.x = 0;
		
		if (IsKeyDown(KEY_D)) {
			helena->velocity.x = PLAYER_HOR_SPEED;
			if (helena->facing == 1 && helena->attacking == false) {
				helena->texture = texRight;
			}
			helena->facing = 0;
		}

		if (IsKeyDown(KEY_A)) {
			helena->velocity.x = -PLAYER_HOR_SPEED;
			if (helena->facing == 0 && helena->attacking == false) {
				helena->texture = texLeft;
			}
			helena->facing = 1;
		}
		
		if (IsKeyDown(KEY_W) && helena->canJump) {
			helena->velocity.y = PLAYER_JUMP_SPEED;
			helena->canJump = false;
		}

		if (IsKeyDown(KEY_SPACE) && helena->attacking == false) {
			a_timer = timer;
			helena->attacking = true;
			if (helena->facing == 0) {
				helena->texture = texAttackRight;
			}
			else if (helena->facing == 1) {
				helena->texture = texAttackLeft;
			}
		}
		
		helena->velocity.y += GRAVITY * dt;
		
		helena->rect.x += helena->velocity.x * dt;
		helena->rect.y += helena->velocity.y * dt;
		
		if (CheckCollisionRecs(helena->rect, floor)) {
			helena->rect.y = floor.y - helena->rect.height;
			helena->velocity.y = 0;
			helena->canJump = true;
		}
		
		
		
		for (int i = 0; i < numPlatforms; i++) {
			if (CheckCollisionRecs(helena->rect, platforms[i])) {
				if (helena->velocity.y > 0) {
					if (helena->rect.y + (helena->rect.height * 0.8) < platforms[i].y) {
						helena->rect.y = platforms[i].y - helena->rect.height;
						helena->velocity.y = 0;
						helena->canJump = true;
					}
				}
			}
		}
		
		UpdateCameraToFollowPlayer(&camera, (Vector2){helena->rect.x, helena->rect.y}, SCREEN_WIDTH, SCREEN_HEIGHT);

		Rectangle rectsource = {0.0f, 0.0f, (float) helena->texture.width, (float) helena->texture.height};
		Rectangle rectdest = helena->rect;
		
		BeginDrawing();
		ClearBackground(SKYBLUE);
		BeginMode2D(camera);
			
			//DrawRectangleRec(helena->rect, WHITE);
			DrawTexturePro(helena->texture, rectsource, rectdest, (Vector2){0, 0}, 0.0f, WHITE);

			DrawRectangleRec(floor, GREEN);
			
			for (int i = 0; i < numPlatforms; i++) {
				DrawRectangleRec(platforms[i], GRAY);
			}
			
		EndDrawing();
		
	}
	
	ToggleBorderlessWindowed();

    UnloadTexture(texRight);
	UnloadTexture(texLeft);
	UnloadTexture(texAttackRight);
	UnloadTexture(texAttackLeft);
	
	CloseWindow();
    
    return 0;
}
