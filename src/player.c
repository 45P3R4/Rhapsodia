
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

    Chunk closestChunks[7] = {
        ch[chunkIndex.x][chunkIndex.y][chunkIndex.z],
        ch[chunkIndex.x+1][chunkIndex.y][chunkIndex.z],
        ch[chunkIndex.x-1][chunkIndex.y][chunkIndex.z],
        ch[chunkIndex.x][chunkIndex.y+1][chunkIndex.z],
        ch[chunkIndex.x][chunkIndex.y-1][chunkIndex.z],
        ch[chunkIndex.x][chunkIndex.y][chunkIndex.z+1],
        ch[chunkIndex.x][chunkIndex.y][chunkIndex.z-1],
    };

    collision = GetRayCollisionMesh(ray, 
        currentChunk.mesh,
        MatrixTranslate(currentChunk.position.x, currentChunk.position.y, currentChunk.position.z));
    
    blockIndex = (Vector3i) {
        (int)(collision.point.x) % CHUNK_SIZE,
        (int)(collision.point.y) % CHUNK_SIZE,
        (int)(collision.point.z) % CHUNK_SIZE };


    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        RayCollision collisionBrake = { 0 };
        
        for (int i = 0; i < 7; i++)
        {
            if (!collisionBrake.hit && collisionBrake.distance < INTERACT_DISTANCE)
            {
                collisionBrake = GetRayCollisionMesh(ray, 
                    currentChunk.mesh,
                    MatrixTranslate(closestChunks[i].position.x, closestChunks[i].position.y, closestChunks[i].position.z));

                    printf("break %d\n", i);
            }
            else
            {
                Vector3i breakPos = {
                    (int)(collisionBrake.point.x - (collisionBrake.normal.x * 0.5)) % CHUNK_SIZE,
                    (int)(collisionBrake.point.y - (collisionBrake.normal.y * 0.5)) % CHUNK_SIZE,
                    (int)(collisionBrake.point.z - (collisionBrake.normal.z * 0.5)) % CHUNK_SIZE };

                printf("break at: [%d, %d, %d] %d\n", breakPos.x, breakPos.y, breakPos.z, i);
                deleteBlock(chunkIndex, breakPos);
                
                break;
            }
        }
        collisionBrake.hit = false;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        RayCollision collisionPlace = { 0 };
        
        for (int i = 0; i < 7; i++)
        {
            if (!collisionPlace.hit && collisionPlace.distance < INTERACT_DISTANCE)
            {
                collisionPlace = GetRayCollisionMesh(ray, 
                    currentChunk.mesh,
                    MatrixTranslate(closestChunks[i].position.x, closestChunks[i].position.y, closestChunks[i].position.z));
            }
            else
            {
                Vector3i placePos = {
                    (int)(collisionPlace.point.x + (collisionPlace.normal.x * 0.5)) % CHUNK_SIZE,
                    (int)(collisionPlace.point.y + (collisionPlace.normal.y * 0.5)) % CHUNK_SIZE,
                    (int)(collisionPlace.point.z + (collisionPlace.normal.z * 0.5)) % CHUNK_SIZE };

                printf("place at: [%d, %d, %d]", placePos.x, placePos.y, placePos.z);
                placeBlock(chunkIndex, placePos, STONE);
                break;
            }
        }
        collisionPlace.hit = !collisionPlace.hit;
    }

    playerDebugDraw();
}