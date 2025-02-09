#include "chunk.h"
#include "noise.h"

int getRandomBlockType() { return (rand() % (TYPES_COUNT-1)) + 1; }

void fillChunkSmooth(Chunk* ch)
{
    ChunkMap noiseMap;

    for (int i = 0; i < pow(CHUNK_SIZE, 3); i++)
    {
        int x = i % CHUNK_SIZE;
        int y = (i / CHUNK_SIZE) % CHUNK_SIZE;
        int z = i / (CHUNK_SIZE * CHUNK_SIZE);

        noiseMap.height[x][z] = floor(pnoise2d(x + ch->position.x, z + ch->position.z, 4, 5, 0)/50) + 3;

        if(y < noiseMap.height[x][z])
            ch->blocks[x][y][z] = getRandomBlockType();
        else
            ch->blocks[x][y][z] = AIR;
    }
}

void fillChunk(Chunk *ch)
{
    for (int i = 0; i < pow(CHUNK_SIZE, 3); i++)
    {
        ch->blocks[i % CHUNK_SIZE][(i / CHUNK_SIZE) % CHUNK_SIZE][i / (CHUNK_SIZE * CHUNK_SIZE)] = getRandomBlockType();
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