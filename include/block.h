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
    FRONT = 0,  // +Z
    BACK = 1,   // -Z
    TOP = 2,    // +Y
    BOTTOM = 3, // -Y
    RIGHT = 4,   // +X
    LEFT = 5   // -X
};

void addFaceVertices(Vector3 position, int side, float* verts, float* normals, float* texturecoords, int* index);

#endif /* BLOCK */
