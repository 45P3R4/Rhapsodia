#ifndef PLAYER
#define PLAYER

#include <raylib.h>
#include <raymath.h>
#include "settings.h"

typedef struct
{
    Camera3D* camera;
    Vector3 position;
    Vector3 up;
    Vector3 size;
} Player;

Player initPlayer(Camera3D* camera, Vector3 position);

bool isOnFloor(Player* player);

void playerUpdate(Player* player, Camera3D* camera);

Vector3 getPlayerForward(Camera* camera);

Vector3 getPlayerUp(Camera* camera);

Vector3 getPlayerRight(Camera* camera);

#endif /* PLAYER */
