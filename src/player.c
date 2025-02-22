
#include "player.h"
#include "world.h"

Ray ray = { 0 };
RayCollision collision = { 0 };
Vector3i chunkIndex = { 0 };  

void playerDrawBlockMarker(RayCollision col)
{
    Vector3 markerPos = {
        (int)(col.point.x - (col.normal.x * 0.5))+0.5,
        (int)(col.point.y - (col.normal.y * 0.5))+0.5,
        (int)(col.point.z - (col.normal.z * 0.5))+0.5 };

    DrawCube(markerPos, 1.01, 1.01, 1.01, (Color){100, 100, 100, 100});
    DrawCube(col.point, 0.1, 0.1, 0.1, BLUE);
    DrawLine3D(col.point, Vector3Add(col.point, col.normal), RED);
}

void playerUpdate(Camera3D camera)
{
    ray = GetScreenToWorldRay((Vector2){GetScreenWidth()/2, GetScreenHeight()/2}, camera);

    chunkIndex = (Vector3i){
        camera.position.x / CHUNK_SIZE,
        camera.position.y / CHUNK_SIZE,
        camera.position.z / CHUNK_SIZE };

    Chunk currentChunk;

    
    const int chunkMask[18][3] = {
        { 0,  0,  0 }, { 1,  0,  0 }, { 0,  1,  0 }, { 0,  0,  1 },
        {-1,  0,  0 }, { 0, -1,  0 }, { 0,  0, -1 }, { 1,  1,  0 },
        { 1, -1,  0 }, { 1,  0,  1 }, { 1,  0, -1 }, { 1,  1,  1 },
        { 1,  1, -1 }, { 1, -1, -1 }, {-1, -1, -1 }, { 0,  1,  1 },
        { 0, -1,  1 }, { 0,  1, -1 }
    };

    for (int i = 0; i < 18; i ++)
    {
        int blockX = chunkMask[i][0];
        int blockY = chunkMask[i][1];
        int blockZ = chunkMask[i][2];

        //is in bounds
        if (blockX > 0 && chunkIndex.x >= CHUNKS_COUNT_X-1)
        blockX = 0;
        if (blockY > 0 && chunkIndex.y >= CHUNKS_COUNT_Y-1)
            blockY = 0;
        if (blockZ  > 0 && chunkIndex.z >= CHUNKS_COUNT_Z-1)
            blockZ  = 0;

        if (blockX < 0 && chunkIndex.x <= 0)
            blockX = 0;
        if (blockY < 0 && chunkIndex.y <= 0)
            blockY = 0;
        if (blockZ  < 0 && chunkIndex.z <= 0)
            blockZ  = 0;

        currentChunk = getChunk(chunkIndex.x + blockX, chunkIndex.y + blockY, chunkIndex.z + blockZ);

        collision = GetRayCollisionMesh(ray, 
            currentChunk.mesh,
            MatrixTranslate(currentChunk.position.x, currentChunk.position.y, currentChunk.position.z));

        if (collision.hit && collision.distance <= INTERACT_DISTANCE)
        {
            chunkIndex = (Vector3i) {chunkIndex.x + blockX, chunkIndex.y + blockY, chunkIndex.z + blockZ};
            break;
        }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector3i breakPos = {
            (int)(collision.point.x - (collision.normal.x * 0.5)) % CHUNK_SIZE,
            (int)(collision.point.y - (collision.normal.y * 0.5)) % CHUNK_SIZE,
            (int)(collision.point.z - (collision.normal.z * 0.5)) % CHUNK_SIZE };

        deleteBlock(chunkIndex, breakPos);
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        Vector3i placePos = {
            (int)(collision.point.x + (collision.normal.x * 0.5)) % CHUNK_SIZE,
            (int)(collision.point.y + (collision.normal.y * 0.5)) % CHUNK_SIZE,
            (int)(collision.point.z + (collision.normal.z * 0.5)) % CHUNK_SIZE };

        placeBlock(chunkIndex, placePos, STONE);
    }

    playerDrawBlockMarker(collision);
}