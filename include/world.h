#ifndef WORLD
#define WORLD

#include "raylib.h"
#include "chunk.h"

#define CHUNKS_COUNT 16

extern Color skyColor;

void worldInit();

void drawChunks();

#endif /* WORLD */
