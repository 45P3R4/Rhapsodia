#ifndef BLOCK
#define BLOCK

#include "raylib.h"

#define SIDE_VERTICES_COUNT 12

enum BlockType
{
    AIR,
    DIRT,
    STONE,
    TYPES_COUNT
};

enum Side {
    RIGHT = 0,   // +X
    LEFT = 1,    // -X
    TOP = 2,     // +Y
    BOTTOM = 3,  // -Y
    FORWARD = 4, // +Z
    BACK = 5     // -Z
};

void addFaceVertices(Vector3 position, int side, float* verts, float* normals, float* texturecoords, int offset);

#endif /* BLOCK */
