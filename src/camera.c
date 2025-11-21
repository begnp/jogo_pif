#include "camera.h"

Camera2D InitCamera(Vector2 target, Vector2 offset) {
    Camera2D camera;
    camera.target = target;
    camera.offset = offset;
    camera.rotation = 0.0f;
    camera.zoom = 1.3f;
    return camera;
}

void UpdateCameraToFollowPlayer(Camera2D *camera, Vector2 playerPos, int screenWidth, int screenHeight, float mapWidth, float mapHeight) {
    Vector2 newTarget;
    newTarget.x = playerPos.x + 32;
    newTarget.y = playerPos.y - 50;

    float viewWidth = screenWidth / camera->zoom;
    float viewHeight = screenHeight / camera->zoom;

    float minX = viewWidth / 2.0f;
    float minY = viewHeight / 2.0f;
    
    float maxX = mapWidth - (viewWidth / 2.0f);
    float maxY = mapHeight - (viewHeight / 2.0f);

    if (newTarget.x < minX) newTarget.x = minX;
    if (newTarget.x > maxX) newTarget.x = maxX;

    if (newTarget.y < minY) newTarget.y = minY;
    if (newTarget.y > maxY) newTarget.y = maxY;

    camera->target = newTarget;
}