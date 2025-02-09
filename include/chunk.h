#ifndef CHUNK
#define CHUNK

#include "raylib.h"
#include "block.h"

#include <stdlib.h> //rand
#include <stdio.h>
#include <math.h>

#define CHUNK_SIZE 16

typedef struct
{
    Vector3i position;
    int blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
} Chunk;

typedef struct
{
    int height[CHUNK_SIZE][CHUNK_SIZE];
} ChunkMap;

void fillByArray(Chunk* ch);

void fillChunkDiagonal(Chunk *ch);

void fillChunkRandom(Chunk *ch);

void drawChunk(Chunk ch);

#endif /* CHUNK */
