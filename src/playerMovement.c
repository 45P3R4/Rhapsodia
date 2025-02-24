#include "playerMovement.h"
#include <raymath.h>
#include "utils.h"

const float moveSpeed = 0.03;

void playerMove(Player* player, Camera *camera, Vector3 direction, float speed)
{
    Vector3 vector = direction;

    vector.y = 0;
    vector = Vector3Normalize(vector);

    vector = Vector3Scale(vector, speed);

    player->position = Vector3Add(player->position, vector);
    camera->position = Vector3Add(camera->position, vector);
    camera->target = Vector3Add(camera->target, vector);
}

void updatePlayerMovement(Player* player, Camera *camera)
{
    // player->position = camera->position;
    Vector3 forward = getPlayerForward(camera);
    Vector3 right = getPlayerRight(camera);

    if (IsKeyDown(KEY_W)) playerMove(player, camera, forward, moveSpeed);
    if (IsKeyDown(KEY_S)) playerMove(player, camera, forward, -moveSpeed);
    if (IsKeyDown(KEY_A)) playerMove(player, camera, right, -moveSpeed);
    if (IsKeyDown(KEY_D)) playerMove(player, camera, right, moveSpeed);
}