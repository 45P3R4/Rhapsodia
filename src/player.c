
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

    Chunk currentChunk = getChunk(chunkIndex.x, chunkIndex.y, chunkIndex.z);

    
    int chunkMask[] = {
        0,  0,  0,
        1,  0,  0,
        0,  1,  0,
        0,  0,  1,

        -1, 0,  0,
        0, -1,  0,
        0,  0, -1,

        1,  1,  0,
        1, -1,  0,

        1,  0,  1,
        1,  0, -1,

        1,  1,  1,
        1,  1, -1,
        1, -1, -1,
       -1, -1, -1,
    
        0,  1,  1,
        0, -1,  1,
        0,  1, -1 };

    for (int i = 0; i < 18; i ++)
    {
        int x = chunkMask[i*3];
        int y = chunkMask[i*3+1];
        int z = chunkMask[i*3+2];

        if (x > 0 && chunkIndex.x == CHUNK_SIZE-1)
            x = 0;
        if (y > 0 && chunkIndex.y == CHUNK_SIZE-1)
            y = 0;
        if (z > 0 && chunkIndex.z == CHUNK_SIZE-1)
            z = 0;

        if (x < 0 && chunkIndex.x == 0)
            x = 0;
        if (y < 0 && chunkIndex.y == 0)
            y = 0;
        if (z < 0 && chunkIndex.z == 0)
            z = 0;

        currentChunk = getChunk(chunkIndex.x + x, chunkIndex.y + y, chunkIndex.z + z);
        // printf("%d: [%d %d %d]\n", i, chunkIndex.x + chunkMask[i*3], chunkIndex.y + chunkMask[i*3+1], chunkIndex.z + chunkMask[i*3+2]);

        collision = GetRayCollisionMesh(ray, 
            currentChunk.mesh,
            MatrixTranslate(currentChunk.position.x, currentChunk.position.y, currentChunk.position.z));

        if (collision.hit && collision.distance <= INTERACT_DISTANCE)
        {
            chunkIndex = (Vector3i) {chunkIndex.x + x, chunkIndex.y + y, chunkIndex.z + z};
            printf("%d\n", i);
            break;
        }
    }

    // collision = GetRayCollisionMesh(ray, 
    //     currentChunk.mesh,
    //     MatrixTranslate(currentChunk.position.x, currentChunk.position.y, currentChunk.position.z));

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