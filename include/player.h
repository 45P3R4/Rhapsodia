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
    Camera3D* camera;
    Vector3 position;
} Player;

Player initPlayer(Camera3D* camera, Vector3 position);

void playerUpdate(Player* player, Camera3D camera);

#endif /* PLAYER */
