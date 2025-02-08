#ifndef CHUNK
#define CHUNK

#include "raylib.h"
#include "block.h"

#include <stdlib.h> //rand
#include <math.h>

#define CHUNK_SIZE 16

typedef struct {
    Vector3i position;
    int blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
} Chunk;


void fillChankRandom(Chunk* ch) {
    for (int i = 0; i < pow(CHUNK_SIZE, 3); i++){
        int x = i % CHUNK_SIZE;
        int y = (i / CHUNK_SIZE) % CHUNK_SIZE;
        int z = i / (CHUNK_SIZE * CHUNK_SIZE);

        int type = rand() % 3;
        switch (type)
        {
        case DIRT:
            ch->blocks[x][y][z] = DIRT;
            break;
        case STONE:
            ch->blocks[x][y][z] = STONE;
            
        default:
            break;
        }
    }
}

void drawChunk(Chunk ch) {
    for (int i = 0; i < pow(CHUNK_SIZE, 3); i++) {
        int x = i % CHUNK_SIZE;
        int y = (i / CHUNK_SIZE) % CHUNK_SIZE;
        int z = i / (CHUNK_SIZE * CHUNK_SIZE);

        int xPos = x + ch.position.x;
        int yPos = y + ch.position.y;
        int zPos = z + ch.position.z;
        
        if (ch.blocks[x][y][z] == DIRT)
            DrawBlock((Vector3i){xPos, yPos, zPos}, BROWN);
        if (ch.blocks[x][y][z] == STONE)
            DrawBlock((Vector3i){xPos, yPos, zPos}, GRAY);
    }
}

#endif /* CHUNK */
