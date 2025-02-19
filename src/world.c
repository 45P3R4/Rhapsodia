#include <stdlib.h>
#include "world.h"

Color skyColor = (Color){135, 206, 235, 255};

Chunk chunks[CHUNKS_COUNT_X][CHUNKS_COUNT_Y][CHUNKS_COUNT_Z];
	
void worldInit()
{
    for (int i = 0; i < CHUNKS_COUNT; i++) 
    {
        int x = i / (CHUNKS_COUNT_Y * CHUNKS_COUNT_Z);  // вычисляем индекс по оси X
        int y = (i % (CHUNKS_COUNT_Y * CHUNKS_COUNT_Z)) / CHUNKS_COUNT_Z;  // вычисляем индекс по оси Y
        int z = i % CHUNKS_COUNT_Z;  // вычисляем индекс по оси Z

        chunks[x][y][z].position = (Vector3){x*CHUNK_SIZE, y*CHUNK_SIZE, z*CHUNK_SIZE};
        fillChunkPerlin(&(chunks[x][y][z]), STONE);
    }
    for (int i = 0; i < CHUNKS_COUNT; i++) 
    {
        int x = i / (CHUNKS_COUNT_Y * CHUNKS_COUNT_Z);  // вычисляем индекс по оси X
        int y = (i % (CHUNKS_COUNT_Y * CHUNKS_COUNT_Z)) / CHUNKS_COUNT_Z;  // вычисляем индекс по оси Y
        int z = i % CHUNKS_COUNT_Z;  // вычисляем индекс по оси Z

        // chunks[x][y][z].position = (Vector3){x*CHUNK_SIZE, y*CHUNK_SIZE, z*CHUNK_SIZE};
        // fillChunkPerlin(&(chunks[x][y][z]), STONE);
        
        chunks[x][y][z].mesh = genMeshChunk((Vector3i){x, y, z});
        chunks[x][y][z].model = LoadModelFromMesh(chunks[x][y][z].mesh);
        chunks[x][y][z].model.materials[0].maps->texture = LoadTexture("resources/test.png");
    }
}

void drawChunks()
{
    for (int i = 0; i < CHUNKS_COUNT; i++) 
    {
        int x = i / (CHUNKS_COUNT_Y * CHUNKS_COUNT_Z);  // вычисляем индекс по оси X
        int y = (i % (CHUNKS_COUNT_Y * CHUNKS_COUNT_Z)) / CHUNKS_COUNT_Z;  // вычисляем индекс по оси Y
        int z = i % CHUNKS_COUNT_Z;  // вычисляем индекс по оси Z

        DrawModel(chunks[x][y][z].model, chunks[x][y][z].position, 1, WHITE);
    }
}

void updateChunk(int chunkX, int chunkY,  int chunkZ)
{
    // UnloadMesh(chunks[chunkX][chunkY][chunkZ].mesh);
    UnloadModel(chunks[chunkX][chunkY][chunkZ].model);
    UnloadTexture(chunks[chunkX][chunkY][chunkZ].model.materials[0].maps->texture);
    chunks[chunkX][chunkY][chunkZ].mesh = genMeshChunk((Vector3i){chunkX, chunkY, chunkZ});
    chunks[chunkX][chunkY][chunkZ].model = LoadModelFromMesh(chunks[chunkX][chunkY][chunkZ].mesh);
    chunks[chunkX][chunkY][chunkZ].model.materials[0].maps->texture = LoadTexture("resources/test.png");
}

void deleteBlock(Vector3i chunkIndex, Vector3i blockIndex)
{
    chunks[(int)chunkIndex.x][(int)chunkIndex.y][(int)chunkIndex.z]
    .blocks[(int)blockIndex.x][(int)blockIndex.y][(int)blockIndex.z] = AIR;

    updateChunk((int)chunkIndex.x, (int)chunkIndex.y, (int)chunkIndex.z);
}

void placeBlock(Vector3i chunkIndex, Vector3i blockIndex, int blockType)
{
    chunks[(int)chunkIndex.x][(int)chunkIndex.y][(int)chunkIndex.z]
    .blocks[(int)blockIndex.x][(int)blockIndex.y][(int)blockIndex.z] = blockType;

    updateChunk((int)chunkIndex.x, (int)chunkIndex.y, (int)chunkIndex.z);
}

Chunk getChunk(int x, int y, int z)
{
    return chunks[x][y][z];
}