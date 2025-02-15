#include <stdlib.h>
#include "world.h"

Color skyColor = (Color){135, 206, 235, 255};

Chunk chunks[CHUNK_SIZE][CHUNK_SIZE];
	
void worldInit()
{
    for (int i = 0; i < CHUNKS_COUNT * CHUNKS_COUNT; i++)
    { 
        int x = i / CHUNKS_COUNT;
        int z = i % CHUNKS_COUNT;

        chunks[x][z].position = (Vector3){x*CHUNK_SIZE, 0, z*CHUNK_SIZE};
        fillChunkSmooth(&(chunks[x][z]), STONE);
        
        chunks[x][z].mesh = genMeshChunk(chunks, x, z);
        chunks[x][z].model = LoadModelFromMesh(chunks[x][z].mesh);
        chunks[x][z].model.materials[0].maps->texture = LoadTexture("resources/test.png");
    }
}

void drawChunks()
{
    for (int i = 0; i < CHUNKS_COUNT * CHUNKS_COUNT; i++)
    {
        int x = i / CHUNKS_COUNT;
        int z = i % CHUNKS_COUNT;

        DrawModel(chunks[x][z].model, (Vector3){0,0,0}, 1, WHITE);
    }
}

void updateChunk(int chunkX, int chunkZ)
{
    printf("\nupdate: [x: %d, z: %d]\n", chunkX, chunkZ);
    // UnloadMesh(chunks[chunkX][chunkZ].mesh);
    // UnloadModel(chunks[chunkX][chunkZ].model);

    chunks[chunkX][chunkZ].mesh = genMeshChunk(chunks, chunkX, chunkZ);
    chunks[chunkX][chunkZ].model = LoadModelFromMesh(chunks[chunkX][chunkZ].mesh);
    chunks[chunkX][chunkZ].model.materials[0].maps->texture = LoadTexture("resources/test.png");
}

void deleteBlock(int chunkX, int chunkY, int chunkZ, int blockX, int blockY, int blockZ)
{
    printf("\ndelete on:\n\tchunk:[%d, %d, %d]\n\tblock:[%d, %d, %d]\n", chunkX, chunkY, chunkZ, blockX, blockY, blockZ);
    printf("block: %d\n", chunks[chunkX][chunkZ].blocks[blockX][blockY][blockZ]);
    chunks[chunkX][chunkZ].blocks[blockX][blockY][blockZ] = AIR;
    printf("block after: %d\n", chunks[chunkX][chunkZ].blocks[blockX][blockY][blockZ]);
    updateChunk(chunkX, chunkZ);
}