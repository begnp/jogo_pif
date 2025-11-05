#include "raylib.h"

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib + C + VSCode");
    SetTargetFPS(60);

    Vector2 ball = { 400, 225 };
    Vector2 speed = { 200, 150 };
    float radius = 20;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        ball.x += speed.x * dt;
        ball.y += speed.y * dt;

        if (ball.x < radius || ball.x > screenWidth - radius) speed.x *= -1;
        if (ball.y < radius || ball.y > screenHeight - radius) speed.y *= -1;

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Hello, raylib!", 20, 20, 20, DARKGRAY);
            DrawCircleV(ball, radius, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
