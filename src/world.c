#include <stdlib.h>
#include "world.h"

Color skyColor = (Color){135, 206, 235, 255};

Chunk chunks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
	
void worldInit()
{
    for (int i = 0; i < pow(CHUNKS_COUNT, 3); i++)
    {
        int x = i % CHUNKS_COUNT;
        int y = (i / CHUNKS_COUNT) % CHUNKS_COUNT;
        int z = i / (CHUNKS_COUNT * CHUNKS_COUNT);

        chunks[x][y][z].position = (Vector3){x*CHUNK_SIZE, y*CHUNK_SIZE, z*CHUNK_SIZE};
        fillChunkPerlin(&(chunks[x][y][z]), STONE);
        
        chunks[x][y][z].mesh = genMeshChunk(chunks, x, y, z);
        chunks[x][y][z].model = LoadModelFromMesh(chunks[x][y][z].mesh);
        chunks[x][y][z].model.materials[0].maps->texture = LoadTexture("resources/test.png");
    }
}

void drawChunks()
{
    for (int i = 0; i < pow(CHUNKS_COUNT, 3); i++)
    {
        int x = i % CHUNKS_COUNT;
        int y = (i / CHUNKS_COUNT) % CHUNKS_COUNT;
        int z = i / (CHUNKS_COUNT * CHUNKS_COUNT);

        DrawModel(chunks[x][y][z].model, (Vector3){0,0,0}, 1, WHITE);
    }
}

void updateChunk(int chunkX, int chunkY,  int chunkZ)
{
    printf("\nupdate: [x: %d, z: %d]\n", chunkX, chunkZ);
    // UnloadMesh(chunks[chunkX][chunkY][chunkZ].mesh);
    // UnloadModel(chunks[chunkX][chunkY][chunkZ].model);

    chunks[chunkX][chunkY][chunkZ].mesh = genMeshChunk(chunks, chunkX, chunkY, chunkZ);
    chunks[chunkX][chunkY][chunkZ].model = LoadModelFromMesh(chunks[chunkX][chunkY][chunkZ].mesh);
    chunks[chunkX][chunkY][chunkZ].model.materials[0].maps->texture = LoadTexture("resources/test.png");
}

void deleteBlock(int chunkX, int chunkY, int chunkZ, int blockX, int blockY, int blockZ)
{
    printf("\ndelete on:\n\tchunk:[%d, %d, %d]\n\tblock:[%d, %d, %d]\n", chunkX, chunkY, chunkZ, blockX, blockY, blockZ);
    printf("block: %d\n", chunks[chunkX][chunkY][chunkZ].blocks[blockX][blockY][blockZ]);
    chunks[chunkX][chunkY][chunkZ].blocks[blockX][blockY][blockZ] = AIR;
    printf("block after: %d\n", chunks[chunkX][chunkY][chunkZ].blocks[blockX][blockY][blockZ]);
    updateChunk(chunkX, chunkY, chunkZ);
}