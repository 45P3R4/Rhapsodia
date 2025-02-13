#ifndef CHUNK
#define CHUNK

#include "raylib.h"
#include "block.h"
#include "noise.h"

#include <stdlib.h> //rand
#include <stdio.h>
#include <math.h>

#define CHUNK_SIZE 4

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

void fillChunkSmooth(Chunk* ch, int blockType);

void fillChunk(Chunk *ch, int blockType);

Mesh genMeshChunk(Chunk ch);

#endif /* CHUNK */
