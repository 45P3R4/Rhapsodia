#ifndef BLOCK
#define BLOCK

#include "raylib.h"

#define SIDE_VERTICES_COUNT 12

enum Block
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
    LEFT = 4,   // +X
    RIGHT = 5   // -X
};

void DrawBlock(Vector3i position, int block, bool top, bool bottom, bool front, bool back, bool left, bool right);

Mesh genMeshBlock(Vector3 position, int block);

void addFaceVertices(Vector3 position, int side, float* verts, float* normals, float* texturecoords, int* index);

#endif /* BLOCK */
