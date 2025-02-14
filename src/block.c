#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include "block.h"

const float frontNormals[] = { 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 };
const float backNormals[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const float topNormals[] = { 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0 };
const float bottomNormals[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const float rightNormals[] = { 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0 };
const float leftNormals[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

const float frontTexcoords[] = {0, 0, 1, 0, 1, 1, 0, 1 };
const float backTexcoords[] = {1, 0, 1, 1, 0, 1, 0, 0};
const float topTexcoords[] = {0, 1, 0, 0, 1, 0, 1, 1};
const float bottomTexcoords[] = {1, 1, 0, 1, 0, 0, 1, 0};
const float rightTexcoords[] = {1, 0, 1, 1, 0, 1, 0, 0};
const float leftTexcoords[] = {0, 0, 1, 0, 1, 1, 0, 1};

void addFaceVertices(Vector3 position, int side, float* verts, float* normals, float* texturecoords, int* index)
{
    switch (side)
    {
    case FRONT:
        const float frontVertices[] = { 
            position.x + 0, position.y + 0, position.z + 1, 
            position.x + 1, position.y + 0, position.z + 1, 
            position.x + 1, position.y + 1, position.z + 1, 
            position.x + 0, position.y + 1, position.z + 1 };
        memcpy(verts + *index*SIDE_VERTICES_COUNT, frontVertices, SIDE_VERTICES_COUNT * sizeof(float));
        memcpy(normals + *index*SIDE_VERTICES_COUNT, frontNormals, SIDE_VERTICES_COUNT * sizeof(float));
        memcpy(texturecoords + *index*8, frontTexcoords, SIDE_VERTICES_COUNT * sizeof(float));
        break;
    case BACK:
        const float backVertices[] = { 
            position.x + 0, position.y + 0, position.z + 0, 
            position.x + 0, position.y + 1, position.z + 0, 
            position.x + 1, position.y + 1, position.z + 0, 
            position.x + 1, position.y + 0, position.z + 0 };
        memcpy(verts + *index*SIDE_VERTICES_COUNT, backVertices, SIDE_VERTICES_COUNT * sizeof(float));
        memcpy(normals + *index*SIDE_VERTICES_COUNT, backNormals, SIDE_VERTICES_COUNT * sizeof(float));
        memcpy(texturecoords + *index*8, backTexcoords, SIDE_VERTICES_COUNT * sizeof(float));
        break;
    case TOP:
        const float topVertices[] = { 
            position.x + 0, position.y + 1, position.z + 0, 
            position.x + 0, position.y + 1, position.z + 1, 
            position.x + 1, position.y + 1, position.z + 1, 
            position.x + 1, position.y + 1, position.z + 0 };
        memcpy(verts + *index*SIDE_VERTICES_COUNT, topVertices, SIDE_VERTICES_COUNT * sizeof(float));
        memcpy(normals + *index*SIDE_VERTICES_COUNT, topNormals, SIDE_VERTICES_COUNT * sizeof(float));
        memcpy(texturecoords + *index*8, topTexcoords, SIDE_VERTICES_COUNT * sizeof(float));
        break;
    case BOTTOM:
        const float bottomVertices[] = { 
            position.x + 0, position.y + 0, position.z + 0, 
            position.x + 1, position.y + 0, position.z + 0, 
            position.x + 1, position.y + 0, position.z + 1, 
            position.x + 0, position.y + 0, position.z + 1 };
        memcpy(verts + *index*SIDE_VERTICES_COUNT, bottomVertices, SIDE_VERTICES_COUNT * sizeof(float));
        memcpy(normals + *index*SIDE_VERTICES_COUNT, bottomNormals, SIDE_VERTICES_COUNT * sizeof(float));
        memcpy(texturecoords + *index*8, bottomTexcoords, SIDE_VERTICES_COUNT * sizeof(float));
        break;
    case RIGHT:
        const float rightVertices[] = { 
            position.x + 1, position.y + 0, position.z + 0, 
            position.x + 1, position.y + 1, position.z + 0, 
            position.x + 1, position.y + 1, position.z + 1, 
            position.x + 1, position.y + 0, position.z + 1 };
        memcpy(verts + *index*SIDE_VERTICES_COUNT, rightVertices, SIDE_VERTICES_COUNT * sizeof(float));
        memcpy(normals + *index*SIDE_VERTICES_COUNT, rightNormals, SIDE_VERTICES_COUNT * sizeof(float));
        memcpy(texturecoords + *index*8, rightTexcoords, SIDE_VERTICES_COUNT * sizeof(float));
        break;
    case LEFT:
        const float leftVertices[] = { 
            position.x + 0, position.y + 0, position.z + 0, 
            position.x + 0, position.y + 0, position.z + 1, 
            position.x + 0, position.y + 1, position.z + 1, 
            position.x + 0, position.y + 1, position.z + 0 };
        memcpy(verts + *index*SIDE_VERTICES_COUNT, leftVertices, SIDE_VERTICES_COUNT * sizeof(float));
        memcpy(normals + *index*SIDE_VERTICES_COUNT, leftNormals, SIDE_VERTICES_COUNT * sizeof(float));
        memcpy(texturecoords + *index*8, leftTexcoords, SIDE_VERTICES_COUNT * sizeof(float));
        break;

    default:
        return;
    } 
    *index += 1;
}