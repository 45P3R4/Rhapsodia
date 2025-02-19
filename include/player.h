#ifndef PLAYER
#define PLAYER

#include "raylib.h"
#include "raymath.h"
#include "settings.h"
#include "utils.h"
#include "chunk.h"
#include "world.h"

typedef struct
{
    Vector3 position;
    Vector3 size;
} Player;

void playerUpdate(Camera3D camera);

void playerDrawBlockMarker();

#endif /* PLAYER */
