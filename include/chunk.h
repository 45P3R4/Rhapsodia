#ifndef CHUNK
#define CHUNK

#include "raylib.h"
#include "block.h"

#include <stdlib.h> //rand
#include <stdio.h>
#include <math.h>

#define CHUNK_SIZE 16

typedef struct
{
    Vector3i position;
    int blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
} Chunk;

void fillChunkRandom(Chunk *ch)
{
    for (int i = 0; i < pow(CHUNK_SIZE, 3); i++)
    {
        int x = i % CHUNK_SIZE;
        int y = (i / CHUNK_SIZE) % CHUNK_SIZE;
        int z = i / (CHUNK_SIZE * CHUNK_SIZE);

        if(y < 13 || (x > 10 && z < 10)) 
        {
            switch (rand() % 3)
            {
                case 0:
                    ch->blocks[x][y][z] = DIRT;
                    break;
                case 1:
                    ch->blocks[x][y][z] = STONE;
                    break;
                case 2:
                    ch->blocks[x][y][z] = SAND;
                    break;
                case 3:
                    ch->blocks[x][y][z] = AIR;
                    break;
                default:
                    break;
            }
        }
        else
        {
            ch->blocks[x][y][z] = AIR;
        }
    }
}

void drawChunk(Chunk ch)
{
    for (int i = 0; i < pow(CHUNK_SIZE, 3); i++)
    {
        int x = i % CHUNK_SIZE;
        int y = (i / CHUNK_SIZE) % CHUNK_SIZE;
        int z = i / (CHUNK_SIZE * CHUNK_SIZE);

        Vector3i blockPosition = (Vector3i){x + ch.position.x,  y + ch.position.y, z + ch.position.z};

        bool top    = (ch.blocks[x][y][z] != AIR && ch.blocks[x][y+1][z] == AIR && y < CHUNK_SIZE-1);
        bool bottom = (ch.blocks[x][y][z] != AIR && ch.blocks[x][y-1][z] == AIR && y > 0);
        bool front  = (ch.blocks[x][y][z] != AIR && ch.blocks[x][y][z+1] == AIR && z < CHUNK_SIZE-1);
        bool back   = (ch.blocks[x][y][z] != AIR && ch.blocks[x][y][z-1] == AIR && z > 0);
        bool right  = (ch.blocks[x][y][z] != AIR && ch.blocks[x+1][y][z] == AIR && x < CHUNK_SIZE-1);
        bool left   = (ch.blocks[x][y][z] != AIR && ch.blocks[x-1][y][z] == AIR && x > 0);

        DrawBlock(blockPosition, ch.blocks[x][y][z], top, bottom, front, back, left, right);
    }
}

#endif /* CHUNK */
