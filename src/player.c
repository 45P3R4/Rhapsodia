
#include "player.h"

Ray ray = { 0 };                    // Picking line ray
RayCollision collision = { 0 };     // Ray collision hit info
Vector3i chunkIndex = { 0 };  
Vector3i blockIndex = { 0 };  

void playerDebugDraw()
{
    Vector3 markerPos = {
        (int)(collision.point.x - (collision.normal.x * 0.5))+0.5,
        (int)(collision.point.y - (collision.normal.y * 0.5))+0.5,
        (int)(collision.point.z - (collision.normal.z * 0.5))+0.5 };

    Vector3 markerNormalPos = {
        collision.point.x + collision.normal.x,
        collision.point.y + collision.normal.y,
        collision.point.z + collision.normal.z };

    DrawCube(markerPos, 1.01, 1.01, 1.01, (Color){100, 100, 100, 100});
    DrawCube(collision.point, 0.1, 0.1, 0.1, BLUE);
    DrawLine3D(collision.point, markerNormalPos, RED);
}

void playerUpdate(Chunk ch[CHUNKS_COUNT][CHUNKS_COUNT][CHUNKS_COUNT], Camera3D camera)
{
    ray = GetScreenToWorldRay((Vector2){GetScreenWidth()/2, GetScreenHeight()/2}, camera);

    chunkIndex = (Vector3i){
        camera.position.x / CHUNK_SIZE,
        camera.position.y / CHUNK_SIZE,
        camera.position.z / CHUNK_SIZE };

    Chunk currentChunk = ch[chunkIndex.x][chunkIndex.y][chunkIndex.z];

    collision = GetRayCollisionMesh(ray, 
        currentChunk.mesh,
        MatrixTranslate(currentChunk.position.x, currentChunk.position.y, currentChunk.position.z));
    
    blockIndex = (Vector3i) {
        (int)(collision.point.x) % CHUNK_SIZE,
        (int)(collision.point.y) % CHUNK_SIZE,
        (int)(collision.point.z) % CHUNK_SIZE };


    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector3i breakPos = {
            (int)(collision.point.x - (collision.normal.x * 0.5))+0.5,
            (int)(collision.point.y - (collision.normal.y * 0.5))+0.5,
            (int)(collision.point.z - (collision.normal.z * 0.5))+0.5 };

            printf("destroy at: [%d, %d, %d]", breakPos.x, breakPos.y, breakPos.z);

        deleteBlock(chunkIndex, breakPos);
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        Vector3i placePos = {
            (int)(collision.point.x + (collision.normal.x * 0.5))+0.5,
            (int)(collision.point.y + (collision.normal.y * 0.5))+0.5,
            (int)(collision.point.z + (collision.normal.z * 0.5))+0.5 };

        placeBlock(chunkIndex, placePos, STONE);
    }

    playerDebugDraw();
}