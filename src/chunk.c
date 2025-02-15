#include <mem.h>
#include "chunk.h"
#include "settings.h"

#define MAX_MESH_VBO 7

int getRandomBlockType() { return (rand() % (TYPES_COUNT-1)) + 1; }

void fillChunkSmooth(Chunk* ch, int blockType)
{
    heightMap noiseMap;

    for (int i = 0; i < pow(CHUNK_SIZE, 3); i++)
    {
        int x = i % CHUNK_SIZE;
        int y = (i / CHUNK_SIZE) % CHUNK_SIZE;
        int z = i / (CHUNK_SIZE * CHUNK_SIZE);

        noiseMap.height[x][z] = floor(pnoise2d(x + ch->position.x, z + ch->position.z, 4, 5, 0)/50) + 3;

        if(y < noiseMap.height[x][z])
            ch->blocks[x][y][z] = blockType;
        else
            ch->blocks[x][y][z] = AIR;
    }
}

void fillChunk(Chunk *ch, int blockType)
{
    for (int i = 0; i < pow(CHUNK_SIZE, 3); i++)
    {
        int x = i % CHUNK_SIZE;
        int y = (i / CHUNK_SIZE) % CHUNK_SIZE;
        int z = i / (CHUNK_SIZE * CHUNK_SIZE);

        ch->blocks[x][y][z] = blockType;
    }
}


Mesh genMeshChunk(Chunk ch[CHUNK_SIZE][CHUNK_SIZE], int xPos, int zPos)
{
    Mesh mesh = {0};
    mesh.vboId = (unsigned int *)RL_CALLOC(MAX_MESH_VBO, sizeof(unsigned int));

    float *vertices = RL_MALLOC(36 * 3 * CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * sizeof(float));
    float *texcoords = RL_MALLOC(36 * 2 * CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * sizeof(float));
    float *normals = RL_MALLOC(36 * 3 * CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * sizeof(float));

    int verticesCount = 0;
    int texcoordsCount = 0;
    int normalsCount = 0;

    int index = 0;

    for (int i = 0; i < pow(CHUNK_SIZE, 3); i++)
    {
        int x = i % CHUNK_SIZE;
        int y = (i / CHUNK_SIZE) % CHUNK_SIZE;
        int z = i / (CHUNK_SIZE * CHUNK_SIZE);

        Vector3 blockPosition = (Vector3){(float)x + ch[xPos][zPos].position.x,  (float)y + ch[xPos][zPos].position.y, (float)z + ch[xPos][zPos].position.z};

        bool blockIsNotAir = ch[xPos][zPos].blocks[x][y][z] != AIR;

        bool topIsAir    = ch[xPos][zPos].blocks[x][y+1][z] == AIR;
        bool bottomIsAir = ch[xPos][zPos].blocks[x][y-1][z] == AIR;
        bool frontIsAir  = ch[xPos][zPos].blocks[x][y][z+1] == AIR;
        bool backIsAir   = ch[xPos][zPos].blocks[x][y][z-1] == AIR;
        bool rightIsAir  = ch[xPos][zPos].blocks[x+1][y][z] == AIR;
        bool leftIsAir   = ch[xPos][zPos].blocks[x-1][y][z] == AIR;

        bool lastBlockZ = (z == CHUNK_SIZE-1);
        bool lastBlockY = (y == CHUNK_SIZE-1);
        bool lastBlockX = (x == CHUNK_SIZE-1);

        bool firstBlockZ = (z == 0);
        bool firstBlockY = (y == 0);
        bool firstBlockX = (x == 0);

        if(lastBlockZ) 
            if (zPos >= CHUNKS_COUNT-1)
                frontIsAir  = ch[xPos][zPos+1].blocks[x][y][0] == AIR;
            else
                frontIsAir  = false;

        if(lastBlockY) 
            topIsAir  = false;

        if(lastBlockX) 
            if (xPos >= CHUNKS_COUNT-1)
                rightIsAir  = ch[xPos+1][zPos].blocks[0][y][z] == AIR;
            else
                rightIsAir  = false;


        if(firstBlockZ) 
            if (zPos <= 0)
                backIsAir = ch[xPos][zPos-1].blocks[x][y][CHUNK_SIZE] == AIR;
            else
                backIsAir = false;

        if(firstBlockY) 
            bottomIsAir  = false;

        if(firstBlockX) 
            if (xPos <= 0)
                leftIsAir   = ch[xPos-1][zPos].blocks[CHUNK_SIZE][y][z] == AIR;
            else
                leftIsAir   = false;

        
        bool isDrawingSide[6] = {
        (blockIsNotAir && frontIsAir), //front
        (blockIsNotAir && backIsAir), //back
        (blockIsNotAir && topIsAir), //top
        (blockIsNotAir && bottomIsAir), //bottom
        (blockIsNotAir && rightIsAir), //right
        (blockIsNotAir && leftIsAir)}; //left

        if ( (int)x + xPos*CHUNK_SIZE == 19 &&
             (int)y == 12 &&
             (int)z + zPos*CHUNK_SIZE == 16 )
        {

            DrawText(TextFormat("\nfront : %d\n back: %d\n top : %d\n bottom: %d\n right : %d\n left: %d\n\n blockIsNotAir: %d\n backIsAir: %d\n\n",
                isDrawingSide[0],
                isDrawingSide[1],
                isDrawingSide[2],
                isDrawingSide[3],
                isDrawingSide[4],
                isDrawingSide[5],
                blockIsNotAir,
                backIsAir),
                20, 20, 20, GREEN);
        }

        for (int k = 0; k < 6; k++)
            if (isDrawingSide[k])
                addFaceVertices(blockPosition, k, vertices, normals, texcoords, &index);

        verticesCount += 36 * 3;
        texcoordsCount += 36 * 2;
        normalsCount += 36 * 3;
        
    }

    mesh.vertices = (float *)RL_MALLOC(verticesCount * sizeof(float));
    memcpy(mesh.vertices, vertices, verticesCount * sizeof(float));

    mesh.texcoords = (float *)RL_MALLOC(texcoordsCount * sizeof(float));
    memcpy(mesh.texcoords, texcoords, texcoordsCount * sizeof(float));

    mesh.normals = (float *)RL_MALLOC(normalsCount * sizeof(float));
    memcpy(mesh.normals, normals, normalsCount * sizeof(float));

    mesh.vertexCount = verticesCount / 3;
    mesh.triangleCount = (verticesCount / 3) / 2;

    RL_FREE(vertices);
    RL_FREE(texcoords);
    RL_FREE(normals);

    mesh.indices = RL_MALLOC(verticesCount * sizeof(float));

    int k = 0;

    for (int i = 0; i < verticesCount; i += 6)
    {
        mesh.indices[i] = 4*k;
        mesh.indices[i + 1] = 4*k + 1;
        mesh.indices[i + 2] = 4*k + 2;
        mesh.indices[i + 3] = 4*k;
        mesh.indices[i + 4] = 4*k + 2;
        mesh.indices[i + 5] = 4*k + 3;

        k++;
    }

    // Upload vertex data to GPU (static mesh)
    UploadMesh(&mesh, false);

    return mesh;
}