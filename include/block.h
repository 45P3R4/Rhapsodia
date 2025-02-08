#ifndef BLOCK
#define BLOCK

#include "raylib.h"
#include "rlgl.h"

enum Block {
    AIR,
    DIRT,
    STONE
};

void drawFrontFace(Vector3i position, Color color)
{
    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
        rlBegin(RL_TRIANGLES);
            rlColor4ub(color.r, color.g, color.b, color.a);
            rlNormal3f(0.0f, 0.0f, 1.0f);
            rlVertex3f(0, 0, 1);  // Bottom Left
            rlVertex3f(1, 0, 1);  // Bottom Right
            rlVertex3f(0, 1, 1);  // Top Left

            rlVertex3f(1, 1, 1);  // Top Right
            rlVertex3f(0, 1, 1);  // Top Left
            rlVertex3f(1, 0, 1);
        rlEnd();
    rlPopMatrix();
}

void drawBackFace(Vector3i position, Color color)
{
    color = (Color){color.r/2, color.g/2, color.b/2, color.a};
    
    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
        rlBegin(RL_TRIANGLES);
            rlColor4ub(color.r, color.g, color.b, color.a);
            rlNormal3f(0.0f, 0.0f, -1.0f);
            rlVertex3f(0, 0, 0);  // Bottom Left
            rlVertex3f(0, 1, 0);  // Top Left
            rlVertex3f(1, 0, 0);  // Bottom Right

            rlVertex3f(1, 1, 0);  // Top Right
            rlVertex3f(1, 0, 0);  // Bottom Right
            rlVertex3f(0, 1, 0);  // Top Left
        rlEnd();
    rlPopMatrix();
}

void drawTopFace(Vector3i position, Color color)
{
    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
        rlBegin(RL_TRIANGLES);
            rlColor4ub(color.r, color.g, color.b, color.a);
        
            rlNormal3f(0.0f, 1.0f, 0.0f);
            rlVertex3f(0, 1, 0);  // Top Left
            rlVertex3f(0, 1, 1);  // Bottom Left
            rlVertex3f(1, 1, 1);  // Bottom Right

            rlVertex3f(1, 1, 0);  // Top Right
            rlVertex3f(0, 1, 0);  // Top Left
            rlVertex3f(1, 1, 1);  // Bottom Right
        rlEnd();
    rlPopMatrix();
}

void drawBottomFace(Vector3i position, Color color)
{
    color = (Color){color.r/2, color.g/2, color.b/2, color.a};

    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
        rlBegin(RL_TRIANGLES);
            rlColor4ub(color.r, color.g, color.b, color.a);
        
            rlNormal3f(0.0f, -1.0f, 0.0f);
            rlVertex3f(0, 0, 0);  // Top Left
            rlVertex3f(1, 0, 1);  // Bottom Right
            rlVertex3f(0, 0, 1);  // Bottom Left

            rlVertex3f(1, 0, 0);  // Top Right
            rlVertex3f(1, 0, 1);  // Bottom Right
            rlVertex3f(0, 0, 0);  // Top Left
        rlEnd();
    rlPopMatrix();
}

void drawRightFace(Vector3i position, Color color)
{
    color = (Color){color.r/2, color.g/2, color.b/2, color.a};

    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
        rlBegin(RL_TRIANGLES);
            rlColor4ub(color.r, color.g, color.b, color.a);
        
            rlNormal3f(1.0f, 0.0f, 0.0f);
            rlVertex3f(1, 0, 0);  // Bottom Right
            rlVertex3f(1, 1, 0);  // Top Right
            rlVertex3f(1, 1, 1);  // Top Left

            rlVertex3f(1, 0, 1);  // Bottom Left
            rlVertex3f(1, 0, 0);  // Bottom Right
            rlVertex3f(1, 1, 1);  // Top Left
        rlEnd();
    rlPopMatrix();
}

void drawLeftFace(Vector3i position, Color color)
{
    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
        rlBegin(RL_TRIANGLES);
            rlColor4ub(color.r, color.g, color.b, color.a);

            rlNormal3f(-1.0f, 0.0f, 0.0f);
            rlVertex3f(0, 0, 0);  // Bottom Right
            rlVertex3f(0, 1, 1);  // Top Left
            rlVertex3f(0, 1, 0);  // Top Right

            rlVertex3f(0, 0, 1);  // Bottom Left
            rlVertex3f(0, 1, 1);  // Top Left
            rlVertex3f(0, 0, 0);  // Bottom Right
        rlEnd();
    rlPopMatrix();
}


void DrawBlock(Vector3i position, Color color)
{
    drawTopFace(position, color);
    drawBottomFace(position, color);
    drawFrontFace(position, color);
    drawBackFace(position, color);
    drawRightFace(position, color);
    drawLeftFace(position, color);
}

#endif /* BLOCK */
