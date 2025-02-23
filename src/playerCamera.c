#include "playerCamera.h"
#include <raymath.h>
#include "player.h"

void lookYaw(Camera3D* camera, float angle)
{
    Vector3 up = camera->up;
    Vector3 targetPosition = Vector3Subtract(camera->target, camera->position);

    targetPosition = Vector3RotateByAxisAngle(targetPosition, up, angle);
    camera->target = Vector3Add(camera->position, targetPosition);
}

void lookPitch(Camera *camera, float angle)
{
    Vector3 up = getPlayerUp(camera);
    Vector3 targetPosition = Vector3Subtract(camera->target, camera->position);

    float maxAngleUp = Vector3Angle(up, targetPosition);
    maxAngleUp -= 0.001f;
    if (angle > maxAngleUp) angle = maxAngleUp;

    float maxAngleDown = Vector3Angle(Vector3Negate(up), targetPosition);
    maxAngleDown *= -1.0f;
    maxAngleDown += 0.001f;
    if (angle < maxAngleDown) angle = maxAngleDown;

    Vector3 right = getPlayerRight(camera);

    targetPosition = Vector3RotateByAxisAngle(targetPosition, right, angle);

    camera->target = Vector3Add(camera->position, targetPosition);
}

void updateLook(Camera* camera)
{
    Vector2 mousePositionDelta = GetMouseDelta();
    float cameraMoveSpeed = 0.5*GetFrameTime();

    lookYaw(camera, -mousePositionDelta.x*MOUSE_SENSITIVITY);
    lookPitch(camera, -mousePositionDelta.y*MOUSE_SENSITIVITY);
}