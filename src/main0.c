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

	Image r0 = LoadImage("./assets/Ellie_f0_right.png");
	Image r1 = LoadImage("./assets/Ellie_f0_left.png");
	
	Image r0_a = LoadImage("./assets/Ellie_f_a_right.png");
	Image r1_a = LoadImage("./assets/Ellie_f_a_left.png");


    Player player = {0};
	player.texture = LoadTextureFromImage(r0);
	player.position.x = SCREEN_WIDTH / 2.0f;
    player.position.y = SCREEN_HEIGHT - 100.0f;
    player.rect.x = player.position.x;
    player.rect.y = player.position.y;
    player.rect.width = (float) player.texture.width * 0.2;
    player.rect.height = (float) player.texture.height * 0.2;
    player.velocity = (Vector2){0, 0};
    player.canJump = false;
	player.attacking = false;
	player.facing = 0;

	float a_timer = 0;
	
	Rectangle floor = {0, SCREEN_HEIGHT - 20, SCREEN_WIDTH, 20};
    
    Rectangle platforms[] = {
		{300, 350, 100, 20},
        {100, 300, 200, 20},
        {400, 200, 150, 20},
        {500, 100, 100, 20}
    };
    int numPlatforms = sizeof(platforms) / sizeof(platforms[0]);
	
	SetTargetFPS(60);

	Camera2D camera = InitCamera((Vector2){player.rect.x, player.rect.y}, (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});
	
	while(!WindowShouldClose()) {

		double timer = GetTime();

		float dt = GetFrameTime();

		// printf("%f\n\n", timer);

		if (player.attacking == true && (timer > a_timer + 0.5)) {
			player.attacking = false;
			if (player.facing == 0) {
				player.texture = LoadTextureFromImage(r0);
			}
			else if (player.facing == 1) {
				player.texture = LoadTextureFromImage(r1);
			}
		}

		/* if (IsKeyPressed(KEY_F11)) {
			ToggleFullscreen();
		} */
		
		player.velocity.x = 0;
		
		if (IsKeyDown(KEY_D)) {
			player.velocity.x = PLAYER_HOR_SPEED;
			if (player.facing == 1 && player.attacking == false) {
				player.texture = LoadTextureFromImage(r0);
			}
			player.facing = 0;
		}

		if (IsKeyDown(KEY_A)) {
			player.velocity.x = -PLAYER_HOR_SPEED;
			if (player.facing == 0 && player.attacking == false) {
				player.texture = LoadTextureFromImage(r1);
			}
			player.facing = 1;
		}
		
		if (IsKeyDown(KEY_W) && player.canJump) {
			player.velocity.y = PLAYER_JUMP_SPEED;
			player.canJump = false;
		}

		if (IsKeyDown(KEY_SPACE) && player.attacking == false) {
			a_timer = timer;
			player.attacking = true;
			if (player.facing == 0) {
				player.texture = LoadTextureFromImage(r0_a);
			}
			else if (player.facing == 1) {
				player.texture = LoadTextureFromImage(r1_a);
			}
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
					if (player.rect.y + (player.rect.height * 0.8) < platforms[i].y) {
						player.rect.y = platforms[i].y - player.rect.height;
						player.velocity.y = 0;
						player.canJump = true;
					}
				}
			}
		}
		
		UpdateCameraToFollowPlayer(&camera, (Vector2){player.rect.x, player.rect.y}, SCREEN_WIDTH, SCREEN_HEIGHT);

		Rectangle rectsource = {0.0f, 0.0f, (float) player.texture.width, (float) player.texture.height};
		Rectangle rectdest = player.rect;
		
		BeginDrawing();
		ClearBackground(SKYBLUE);
		BeginMode2D(camera);
			
			//DrawRectangleRec(player.rect, WHITE);
			DrawTexturePro(player.texture, rectsource, rectdest, (Vector2){0, 0}, 0.0f, WHITE);

			DrawRectangleRec(floor, GREEN);
			
			for (int i = 0; i < numPlatforms; i++) {
				DrawRectangleRec(platforms[i], GRAY);
			}
			
		EndDrawing();
		
	}
	
	ToggleBorderlessWindowed();

    UnloadTexture(player.texture);
	
	CloseWindow();
    
    return 0;
}
