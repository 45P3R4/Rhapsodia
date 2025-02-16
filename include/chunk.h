#ifndef CHUNK
#define CHUNK

#include "raylib.h"
#include "block.h"
#include "noise.h"
#include "settings.h"

#include <stdlib.h> //rand
#include <stdio.h>
#include <math.h>

typedef struct
{
    Vector3 position;
    int blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
    Mesh mesh;
    Model model;
} Chunk;

typedef struct
{
    int height[CHUNK_SIZE][CHUNK_SIZE];
} heightMap;

void fillChunkPerlin(Chunk* ch, int blockType);

void fillChunk(Chunk *ch, int blockType);

Mesh genMeshChunk(Chunk ch[CHUNKS_COUNT][CHUNKS_COUNT][CHUNKS_COUNT], int chunkX, int chunkY, int chunkZ);

#endif /* CHUNK */
