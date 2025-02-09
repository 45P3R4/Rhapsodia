#ifndef BLOCK
#define BLOCK

#include "raylib.h"
#include "rlgl.h"

enum Block
{
    AIR,
    DIRT,
    STONE,
    SAND,
    TYPES_COUNT
};

// +Z
void drawFrontFace(Color color);

// -Z
void drawBackFace(Color color);

// +Y
void drawTopFace(Color color);

// -Y
void drawBottomFace(Color color);

// +X
void drawRightFace(Color color);

// -X
void drawLeftFace(Color color);


void DrawBlock(Vector3i position, int block, bool top, bool bottom, bool front, bool back, bool left, bool right);

#endif /* BLOCK */
