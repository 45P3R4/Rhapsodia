#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include "block.h"

float blockVertices[6][12] = {
    {1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1}, //right
    {0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0}, //left
    {0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0}, //top
    {0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1}, //bottom
    {0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1}, //front
    {0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0}}; //back

float blockNormals[6][12] = {
    { 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,}, //right
    { -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0}, //left
    { 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,}, //top
    { 0,-1, 0, 0,-1, 0, 0,-1, 0, 0,-1, 0,}, //bottom
    { 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1}, //front
    { 0, 0,-1, 0, 0,-1, 0, 0,-1, 0, 0,-1}}; //back

float blockTexcoords[6][12] = {
    {1, 0, 1, 1, 0, 1, 0, 0}, //right
    {0, 0, 1, 0, 1, 1, 0, 1}, //left
    {0, 1, 0, 0, 1, 0, 1, 1}, //top
    {1, 1, 0, 1, 0, 0, 1, 0}, //bottom
    {0, 0, 1, 0, 1, 1, 0, 1}, //front
    {1, 0, 1, 1, 0, 1, 0, 0}}; //back
    
    

void addFaceVertices(Vector3 position, int side, float* verts, float* normals, float* texturecoords, int* index)
{
    if (side >= 0 && side < 6)
    {
        const float vertices[] = { 
            position.x + blockVertices[side][0], position.y + blockVertices[side][1], position.z + blockVertices[side][2], 
            position.x + blockVertices[side][3], position.y + blockVertices[side][4], position.z + blockVertices[side][5], 
            position.x + blockVertices[side][6], position.y + blockVertices[side][7], position.z + blockVertices[side][8], 
            position.x + blockVertices[side][9], position.y + blockVertices[side][10], position.z + blockVertices[side][11]};

        memcpy(verts + *index*SIDE_VERTICES_COUNT, vertices, SIDE_VERTICES_COUNT * sizeof(float));
        memcpy(normals + *index*SIDE_VERTICES_COUNT, blockNormals[side], SIDE_VERTICES_COUNT * sizeof(float));
        memcpy(texturecoords + *index*8, blockTexcoords[side], 32);
        *index += 1;
    }
}