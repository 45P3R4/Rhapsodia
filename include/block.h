#ifndef BLOCK
#define BLOCK

#include "raylib.h"
#include "rlgl.h"

enum Block
{
    AIR,
    DIRT,
    STONE,
    SAND
};

// +Z
void drawFrontFace(Color color)
{
    rlBegin(RL_TRIANGLES);
    rlColor4ub(color.r, color.g, color.b, color.a);

    rlNormal3f(0.0f, 0.0f, 1.0f);
    rlVertex3f(0, 0, 1); // Bottom Left
    rlVertex3f(1, 0, 1); // Bottom Right
    rlVertex3f(0, 1, 1); // Top Left

    rlVertex3f(1, 1, 1); // Top Right
    rlVertex3f(0, 1, 1); // Top Left
    rlVertex3f(1, 0, 1);
    rlEnd();
}
// -Z
void drawBackFace(Color color)
{
    color = (Color){color.r / 2, color.g / 2, color.b / 2, color.a};

    rlBegin(RL_TRIANGLES);
    rlColor4ub(color.r, color.g, color.b, color.a);

    rlNormal3f(0.0f, 0.0f, -1.0f);
    rlVertex3f(0, 0, 0); // Bottom Left
    rlVertex3f(0, 1, 0); // Top Left
    rlVertex3f(1, 0, 0); // Bottom Right

    rlVertex3f(1, 1, 0); // Top Right
    rlVertex3f(1, 0, 0); // Bottom Right
    rlVertex3f(0, 1, 0); // Top Left
    rlEnd();
}
// +Y
void drawTopFace(Color color)
{
    rlBegin(RL_TRIANGLES);
    rlColor4ub(color.r, color.g, color.b, color.a);

    rlNormal3f(0.0f, 1.0f, 0.0f);
    rlVertex3f(0, 1, 0); // Top Left
    rlVertex3f(0, 1, 1); // Bottom Left
    rlVertex3f(1, 1, 1); // Bottom Right

    rlVertex3f(1, 1, 0); // Top Right
    rlVertex3f(0, 1, 0); // Top Left
    rlVertex3f(1, 1, 1); // Bottom Right
    rlEnd();
}
// -Y
void drawBottomFace(Color color)
{
    color = (Color){color.r / 2, color.g / 2, color.b / 2, color.a};

    rlBegin(RL_TRIANGLES);
    rlColor4ub(color.r, color.g, color.b, color.a);

    rlNormal3f(0.0f, -1.0f, 0.0f);
    rlVertex3f(0, 0, 0); // Top Left
    rlVertex3f(1, 0, 1); // Bottom Right
    rlVertex3f(0, 0, 1); // Bottom Left

    rlVertex3f(1, 0, 0); // Top Right
    rlVertex3f(1, 0, 1); // Bottom Right
    rlVertex3f(0, 0, 0); // Top Left
    rlEnd();
}
// +X
void drawRightFace(Color color)
{
    color = (Color){color.r / 2, color.g / 2, color.b / 2, color.a};

    rlBegin(RL_TRIANGLES);
    rlColor4ub(color.r, color.g, color.b, color.a);

    rlNormal3f(1.0f, 0.0f, 0.0f);
    rlVertex3f(1, 0, 0); // Bottom Right
    rlVertex3f(1, 1, 0); // Top Right
    rlVertex3f(1, 1, 1); // Top Left

    rlVertex3f(1, 0, 1); // Bottom Left
    rlVertex3f(1, 0, 0); // Bottom Right
    rlVertex3f(1, 1, 1); // Top Left
    rlEnd();
}
// -X
void drawLeftFace(Color color)
{
    rlBegin(RL_TRIANGLES);
    rlColor4ub(color.r, color.g, color.b, color.a);

    rlNormal3f(-1.0f, 0.0f, 0.0f);
    rlVertex3f(0, 0, 0); // Bottom Right
    rlVertex3f(0, 1, 1); // Top Left
    rlVertex3f(0, 1, 0); // Top Right

    rlVertex3f(0, 0, 1); // Bottom Left
    rlVertex3f(0, 1, 1); // Top Left
    rlVertex3f(0, 0, 0); // Bottom Right
    rlEnd();
}

void DrawBlock(Vector3i position, int block, bool top, bool bottom, bool front, bool back, bool left, bool right)
{
    Color color = PINK;

    if (block == DIRT)
        color = BROWN;
    if (block == STONE)
        color = GRAY;
    if (block == SAND)
        color = GOLD;

    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
    
    if (top)
        drawTopFace(color);
    if (bottom)
        drawBottomFace(color);
    if (front)
        drawFrontFace(color);
    if (back)
        drawBackFace(color);
    if (right)
        drawRightFace(color);
    if (left)
        drawLeftFace(color);
    rlPopMatrix();
}

#endif /* BLOCK */
