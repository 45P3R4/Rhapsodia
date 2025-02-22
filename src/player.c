
#include "player.h"
#include "world.h"

Ray ray = { 0 };
RayCollision collision = { 0 };
Vector3i chunkIndex = { 0 };  


void updateNearbyChunks(Vector3i chIndex, Vector3i blockPosition)
{
    if (blockPosition.x >= CHUNK_SIZE-1 && chIndex.x < CHUNKS_COUNT_X -1)
            updateChunk(chIndex.x+1, chIndex.y, chIndex.z);
        if (blockPosition.y >= CHUNK_SIZE-1 && chIndex.y < CHUNKS_COUNT_Y -1)
            updateChunk(chIndex.x, chIndex.y+1, chIndex.z);
        if (blockPosition.z >= CHUNK_SIZE-1 && chIndex.z < CHUNKS_COUNT_Z -1)
            updateChunk(chIndex.x, chIndex.y, chIndex.z+1);

        if (blockPosition.x <= 0 && chIndex.x > 0)
            updateChunk(chIndex.x-1, chIndex.y, chIndex.z);
        if (blockPosition.y <= 0 && chIndex.y > 0)
            updateChunk(chIndex.x, chIndex.y-1, chIndex.z);
        if (blockPosition.z <= 0 && chIndex.z > 0)
            updateChunk(chIndex.x, chIndex.y, chIndex.z-1);
}

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

RayCollision getBlockCollision(Chunk chunkCurrent)
{
    RayCollision col;
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

            chunkCurrent = getChunk(chunkIndex.x + blockX, chunkIndex.y + blockY, chunkIndex.z + blockZ);

        col = GetRayCollisionMesh(ray, 
            chunkCurrent.mesh,
            MatrixTranslate(chunkCurrent.position.x, chunkCurrent.position.y, chunkCurrent.position.z));

        if (col.hit && col.distance <= INTERACT_DISTANCE)
        {
            chunkIndex = (Vector3i) {chunkIndex.x + blockX, chunkIndex.y + blockY, chunkIndex.z + blockZ};
            break;
        }
    }
    return col;
}


void playerUpdate(Camera3D camera)
{
    ray = GetScreenToWorldRay((Vector2){GetScreenWidth()/2, GetScreenHeight()/2}, camera);

    chunkIndex = (Vector3i){
        camera.position.x / CHUNK_SIZE,
        camera.position.y / CHUNK_SIZE,
        camera.position.z / CHUNK_SIZE };

    Chunk currentChunk;

    collision = getBlockCollision(currentChunk);

    playerDrawBlockMarker(collision);
    

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Vector3i breakPos = {
            (int)(collision.point.x - (collision.normal.x * 0.5)) % CHUNK_SIZE,
            (int)(collision.point.y - (collision.normal.y * 0.5)) % CHUNK_SIZE,
            (int)(collision.point.z - (collision.normal.z * 0.5)) % CHUNK_SIZE };

        deleteBlock(chunkIndex, breakPos);

        updateNearbyChunks(chunkIndex, breakPos);
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        Vector3i placePos = {
            (int)(collision.point.x + (collision.normal.x * 0.5)) % CHUNK_SIZE,
            (int)(collision.point.y + (collision.normal.y * 0.5)) % CHUNK_SIZE,
            (int)(collision.point.z + (collision.normal.z * 0.5)) % CHUNK_SIZE };

        placeBlock(chunkIndex, placePos, STONE);

        updateNearbyChunks(chunkIndex, placePos);
    }
}