#ifndef CHUNK
#define CHUNK

#include "raylib.h"
#include "block.h"
#include "noise.h"
#include "settings.h"
#include "utils.h"

#include <stdlib.h> //rand
#include <stdio.h>
#include <math.h>

typedef struct
{
    Vector3 position;
    int height[CHUNK_SIZE][CHUNK_SIZE];
    int blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
    Mesh mesh;
    Model model;
} Chunk;

void fillChunkPerlin(Chunk* ch, int blockType);

void fillChunk(Chunk *ch, int blockType);

Mesh genMeshChunk(Vector3i chunkIndex);

#endif /* CHUNK */
