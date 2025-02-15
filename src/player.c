#include "player.h"

Ray ray = { 0 };                    // Picking line ray
RayCollision collision = { 0 };     // Ray collision hit info

void playerUpdate(Chunk ch[CHUNK_SIZE][CHUNK_SIZE], Camera3D camera)
{
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (!collision.hit)
            {
                ray = GetScreenToWorldRay((Vector2){SCREEN_WIDTH/2, SCREEN_HEIGHT/2}, camera);

                // Check collision between ray and box
                collision = GetRayCollisionBox(ray,
                            (BoundingBox){(Vector3){ 0, 0, 0 },
                                          (Vector3){ CHUNK_SIZE, 9, CHUNK_SIZE }});
            }
            else collision.hit = false;
        }

        Vector3 pos = {(float)((int)collision.point.x)+0.5, (float)((int)collision.point.y)+0.5, (float)((int)collision.point.z)+0.5};
            DrawCube(pos, 1.01, 1.01, 1.01, RED);

        if (collision.hit)
        {
            deleteBlock((int)collision.point.x / 16, 0, (int)collision.point.z / 16, (int)collision.point.x % 16, (int)collision.point.y % 16, (int)collision.point.z % 16);
            printf("block: %d\n", chunks[0][0].blocks[0][8][0]);
            collision.hit = !collision.hit;
        }

        DrawRay(ray, MAROON);
}

void playerDebugInfo()
{
    DrawText(TextFormat("collision distance: [%f]\n", collision.distance), 3, 100, 20, WHITE);
    DrawText(TextFormat("collision hit: [%d]\n", collision.hit), 3, 120, 20, WHITE);
    DrawText(TextFormat("collision normal: [%f, %f, %f]\n", collision.normal.x, collision.normal.y, collision.normal.z), 3, 140, 20, WHITE);
    DrawText(TextFormat("collision point: [%f, %f, %f]\n", collision.point.x, collision.point.y, collision.point.z), 3, 160, 20, WHITE);
}