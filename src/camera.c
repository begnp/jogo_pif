#include "camera.h"

Camera2D InitCamera(Vector2 target, Vector2 offset) {
    Camera2D camera;
    camera.target = target;
    camera.offset = offset;
    camera.rotation = 0.0f;
    camera.zoom = 1.3f;
    return camera;
}

void UpdateCameraToFollowPlayer(Camera2D *camera, Vector2 playerPos, int screenWidth, int screenHeight) {
    Vector2 newTarget;
    newTarget.x = playerPos.x + 32;
    newTarget.y = playerPos.y - 50;

    camera->target = newTarget;
}