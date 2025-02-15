#include <stdlib.h>
#include "settings.h"
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