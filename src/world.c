#include <stdlib.h>
#include "world.h"

Color skyColor = (Color){135, 206, 235, 255};

Chunk chunks[CHUNKS_COUNT][CHUNKS_COUNT];
	

void worldInit()
{
    for (int i = 0; i < CHUNKS_COUNT * CHUNKS_COUNT; i++)
    {
        chunks[i / CHUNKS_COUNT][i % CHUNKS_COUNT].position = (Vector3){i / CHUNKS_COUNT*CHUNK_SIZE, 0, i % CHUNKS_COUNT*CHUNK_SIZE};
        fillChunkSmooth(&(chunks[i / CHUNKS_COUNT][i % CHUNKS_COUNT]), STONE);
        chunks[i / CHUNKS_COUNT][i % CHUNKS_COUNT].mesh = genMeshChunk(chunks[i / CHUNKS_COUNT][i % CHUNKS_COUNT]);
        chunks[i / CHUNKS_COUNT][i % CHUNKS_COUNT].model = LoadModelFromMesh(chunks[i / CHUNKS_COUNT][i % CHUNKS_COUNT].mesh);
    }
}

void drawChunks()
{
    for (int i = 0; i < CHUNKS_COUNT * CHUNKS_COUNT; i++)
    {
        // bool chtop =    true;
        // bool chbottom = true;
        // bool chfront =  true;
        // bool chback =   true;
        // bool chleft =   true;
        // bool chright =  true;

		// drawChunk(chunks[i / CHUNKS_COUNT][i % CHUNKS_COUNT], chtop, chbottom, chfront, chback, chleft, chright);
        // DrawModel(chunks[i / CHUNKS_COUNT][i % CHUNKS_COUNT].model, (Vector3){0,0,0}, 1, WHITE);
    }
}