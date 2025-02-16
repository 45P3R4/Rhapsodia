#ifndef WORLD
#define WORLD

#include "raylib.h"
#include "utils.h"
#include "settings.h"
#include "chunk.h"

extern Color skyColor;
extern Chunk chunks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];

void worldInit();

void drawChunks();

void updateChunk(int chunkX, int chunkY, int chunkZ);

void deleteBlock(Vector3i chunkIndex, Vector3i blockIndex);

void placeBlock(Vector3i chunkIndex, Vector3i blockIndex, int blockType);

#endif /* WORLD */
