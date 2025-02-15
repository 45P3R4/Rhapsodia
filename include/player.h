#ifndef PLAYER
#define PLAYER

#include "raylib.h"
#include "settings.h"
#include "chunk.h"
#include "world.h"

typedef struct
{
    Vector3 position;
    Vector3 size;
} Player;

void playerUpdate(Chunk ch[CHUNK_SIZE][CHUNK_SIZE], Camera3D camera);

void playerDebugInfo();

#endif /* PLAYER */
