#ifndef WORLD
#define WORLD

#include "raylib.h"
#include "settings.h"
#include "chunk.h"

extern Color skyColor;
extern Chunk chunks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];

void worldInit();

void drawChunks();

void updateChunk(int chunkX, int chunkY, int chunkZ);

void deleteBlock(int chunkX, int chunkY, int chunkZ, int blockX, int blockY, int blockZ);

#endif /* WORLD */
