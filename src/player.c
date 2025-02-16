
#include "player.h"

Ray ray = { 0 };                    // Picking line ray
RayCollision collision = { 0 };     // Ray collision hit info
Vector3i chunkIndex = { 0 };  
Vector3i blockIndex = { 0 };  

void playerUpdate(Chunk ch[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE], Camera3D camera)
{
        if (!collision.hit)
        {
            ray = GetScreenToWorldRay((Vector2){GetScreenWidth()/2, GetScreenHeight()/2}, camera);

            Vector3i chIndex = {
                camera.position.x / CHUNK_SIZE,
                camera.position.y / CHUNK_SIZE,
                camera.position.z / CHUNK_SIZE };

            collision = GetRayCollisionMesh(ray, ch[chIndex.x][chIndex.y][chIndex.z].mesh, ch[chIndex.x][chIndex.y][chIndex.z].model.transform);

            chunkIndex = (Vector3i) {
                (int)floor(collision.point.x / CHUNK_SIZE),
                (int)floor(collision.point.y / CHUNK_SIZE),
                (int)floor(collision.point.z / CHUNK_SIZE) };
    
            blockIndex = (Vector3i) {
                (int)(collision.point.x) % CHUNK_SIZE,
                (int)(collision.point.y) % CHUNK_SIZE,
                (int)(collision.point.z) % CHUNK_SIZE };

        }
        else collision.hit = false;

        Vector3 pos = {
            (int)(collision.point.x - (collision.normal.x * 0.5))+0.5,
            (int)(collision.point.y - (collision.normal.y * 0.5))+0.5,
            (int)(collision.point.z - (collision.normal.z * 0.5))+0.5 };

        Vector3i breakPos = {
            (int)(collision.point.x - (collision.normal.x * 0.5))+0.5,
            (int)(collision.point.y - (collision.normal.y * 0.5))+0.5,
            (int)(collision.point.z - (collision.normal.z * 0.5))+0.5 };

        Vector3i placePos = {
            (int)(collision.point.x + (collision.normal.x * 0.5))+0.5,
            (int)(collision.point.y + (collision.normal.y * 0.5))+0.5,
            (int)(collision.point.z + (collision.normal.z * 0.5))+0.5 };

        Vector3 normalPos = {
            collision.point.x + collision.normal.x,
            collision.point.y + collision.normal.y,
            collision.point.z + collision.normal.z };

        DrawCube(pos, 1.01, 1.01, 1.01, (Color){100, 100, 100, 100});
        DrawCube(collision.point, 0.1, 0.1, 0.1, BLUE);
        DrawLine3D(collision.point, normalPos, RED);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            deleteBlock(chunkIndex, breakPos);

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
            placeBlock(chunkIndex, placePos, STONE);

        DrawRay(ray, MAROON);
}