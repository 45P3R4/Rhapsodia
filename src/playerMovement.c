#include "playerMovement.h"
#include <raymath.h>
#include "utils.h"

#include <stdio.h>

const float moveSpeed = 0.03;
const float jumpPower = 5.0;
const float gravity = 0.001f;
float verticalVelocity = 0;
Vector3 velocity = (Vector3) {0,0,0};

void updatePlayerMovement(Player* player, Camera* camera)
{
    player->position = camera->position;

    velocity = (Vector3) {0,0,0};
    Vector3 forward = getPlayerForward(camera);
    Vector3 right = getPlayerRight(camera);

    const Vector3 notY = {1, 0, 1};

    if (IsKeyDown(KEY_W)) velocity = Vector3Add(velocity, Vector3Multiply(forward, (notY)));
    if (IsKeyDown(KEY_S)) velocity = Vector3Subtract(velocity, Vector3Multiply(forward, (notY)));
    if (IsKeyDown(KEY_D)) velocity = Vector3Add(velocity, Vector3Multiply(right, (notY)));
    if (IsKeyDown(KEY_A)) velocity = Vector3Subtract(velocity, Vector3Multiply(right, (notY)));

    velocity = Vector3Normalize(velocity);
    velocity = Vector3Scale(velocity, moveSpeed);

    Vector3 down = (Vector3){0.0f, verticalVelocity, 0.0f};

    if (isOnFloor(player))
    {
        verticalVelocity = 0;

        if(IsKeyPressed(KEY_SPACE))
        {
            verticalVelocity = jumpPower;
        }
    }
    else
        verticalVelocity -= gravity;

    printf("%f\n", verticalVelocity);

    velocity = Vector3Add(velocity, (Vector3){0, verticalVelocity, 0});

    // player->position = Vector3Add(player->position, velocity);
    camera->position = Vector3Add(camera->position, velocity);
    camera->target = Vector3Add(camera->target, velocity);
}