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


	Image player0 = LoadImage("./assets/Ellie_f0_right.png");
	Image player1 = LoadImage("./assets/Ellie_f0_left.png");
	
	Image player0_a = LoadImage("./assets/Ellie_f_a_right.png");
	Image player1_a = LoadImage("./assets/Ellie_f_a_left.png");
    
	Texture2D texPlayerRight = LoadTextureFromImage(player0);
	Texture2D texPlayerLeft = LoadTextureFromImage(player1);
	Texture2D texPlayerAttackRight = LoadTextureFromImage(player0_a);
	Texture2D texPlayerAttackLeft = LoadTextureFromImage(player1_a);

	UnloadImage(player0);
	UnloadImage(player1);
	UnloadImage(player0_a);
	UnloadImage(player1_a);

	Player *helena = (Player *) malloc(sizeof(Player));
	*helena = InitPlayer(helena, texPlayerRight);


	Image imgEnemy0 = LoadImage("./assets/snorlax.png");

	Texture2D texEnem0 = LoadTextureFromImage(imgEnemy0);

	UnloadImage(imgEnemy0);

	Enemy *enemy0 = (Enemy *) malloc(sizeof(Enemy));
	*enemy0 = InitEnemy(enemy0, texEnem0, 0);
	// Enemy *enemy = ;
	// InitEnemy();

	// helena->texture = texPlayerRight; //textura inicial
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
				helena->texture = texPlayerRight;
			}
			else if (helena->facing == 1) {
				helena->texture = texPlayerLeft;
			}
		}

		/* if (IsKeyPressed(KEY_F11)) {
			ToggleFullscreen();
		} */
		
		helena->velocity.x = 0;
		enemy0->velocity.x = 0;
		
		if (IsKeyDown(KEY_D)) {
			helena->velocity.x = PLAYER_HOR_SPEED;
			if (helena->facing == 1 && helena->attacking == false) {
				helena->texture = texPlayerRight;
			}
			helena->facing = 0;
		}

		if (IsKeyDown(KEY_A)) {
			helena->velocity.x = -PLAYER_HOR_SPEED;
			if (helena->facing == 0 && helena->attacking == false) {
				helena->texture = texPlayerLeft;
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
				helena->texture = texPlayerAttackRight;
			}
			else if (helena->facing == 1) {
				helena->texture = texPlayerAttackLeft;
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

		enemy0->velocity.y += GRAVITY * dt;

		enemy0->rect.x += enemy0->velocity.x * dt;
		enemy0->rect.y += enemy0->velocity.y * dt;

		if (CheckCollisionRecs(enemy0->rect, floor)) {
			enemy0->rect.y = floor.y - enemy0->rect.height;
			enemy0->velocity.y = 0;
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

		Rectangle rectsource_e = {0.0f, 0.0f, (float) enemy0->texture.width, (float) enemy0->texture.height};
		Rectangle rectdest_e = enemy0->rect;
		
		BeginDrawing();
		ClearBackground(SKYBLUE);
		BeginMode2D(camera);
			
			//DrawRectangleRec(helena->rect, WHITE);
			DrawTexturePro(helena->texture, rectsource, rectdest, (Vector2){0, 0}, 0.0f, WHITE);

			DrawRectangleRec(enemy0->rect, WHITE);

			DrawTexturePro(enemy0->texture, rectsource_e, rectdest_e, (Vector2){0, 0}, 0.0f, WHITE);

			DrawRectangleRec(floor, GREEN);
			
			for (int i = 0; i < numPlatforms; i++) {
				DrawRectangleRec(platforms[i], GRAY);
			}
			
		EndDrawing();
		
	}
	
	ToggleBorderlessWindowed();

    UnloadTexture(texPlayerRight);
	UnloadTexture(texPlayerLeft);
	UnloadTexture(texPlayerAttackRight);
	UnloadTexture(texPlayerAttackLeft);

	UnloadTexture(texEnem0);
	
	CloseWindow();
    
    return 0;
}
