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
    FRONT,
    BACK,
    TOP,
    BOTTOM,
    LEFT,
    RIGHT
};

// +Z front
// -Z back
// +Y top
// -Y botom
// +X right
// -X left


void DrawBlock(Vector3i position, int block, bool top, bool bottom, bool front, bool back, bool left, bool right);

Mesh genMeshBlock(Vector3 position, int block);

void addFaceVertices(Vector3 position, int side, float* verts, float* normals, int* index);

#endif /* BLOCK */
