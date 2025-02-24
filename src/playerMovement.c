#include "playerMovement.h"
#include <raymath.h>
#include "utils.h"

#include <stdio.h>

const float moveSpeed = 0.03;
const float jumpPower = 50.0;
const float gravity = 0.001f;
float verticalVelocity = 0;
Vector3 velocity = (Vector3) {0,0,0};

int jumpindex = 5;

void updatePlayerMovement(Player* player, Camera* camera)
{
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
            jumpindex = 10;
    }
    else
        verticalVelocity -= gravity;

    if (jumpindex > 0)
    {
        verticalVelocity = gravity * jumpPower/jumpindex;
        jumpindex--;
    }

    velocity = Vector3Add(velocity, (Vector3){0, verticalVelocity, 0});

    camera->position = Vector3Add(camera->position, velocity);
    player->position = camera->position;
    camera->target = Vector3Add(camera->target, velocity);
}