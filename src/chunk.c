#include <string.h>
#include "chunk.h"
#include "world.h"

#define MAX_MESH_VBO 7

int getRandomBlockType() { return (rand() % (TYPES_COUNT-1)) + 1; }

void fillChunkPerlin(Chunk* ch, int blockType)
{
    int noiseMap[CHUNK_SIZE][CHUNK_SIZE];

    for (int i = 0; i < pow(CHUNK_SIZE, 3); i++)
    {
        int x = i % CHUNK_SIZE;
        int y = (i / CHUNK_SIZE) % CHUNK_SIZE;
        int z = i / (CHUNK_SIZE * CHUNK_SIZE);

        noiseMap[x][z] = (int)(pnoise2d(x + ch->position.x, z + ch->position.z, 4, 5, 0)/20) + 3;

        if(y + ch->position.y < noiseMap[x][z])
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


Mesh genMeshChunk(Vector3i chunkIndex)
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

    Chunk currentChunk = getChunk(chunkIndex.x, chunkIndex.y, chunkIndex.z);

    for (int i = 0; i < pow(CHUNK_SIZE, 3); i++)
    {
        int x = i % CHUNK_SIZE;
        int y = (i / CHUNK_SIZE) % CHUNK_SIZE;
        int z = i / (CHUNK_SIZE * CHUNK_SIZE);

        bool blockIsNotAir = currentChunk.blocks[x][y][z] != AIR;

        bool rightIsAir  = currentChunk.blocks[x+1][y][z] == AIR;
        bool leftIsAir   = currentChunk.blocks[x-1][y][z] == AIR;
        bool topIsAir    = currentChunk.blocks[x][y+1][z] == AIR;
        bool bottomIsAir = currentChunk.blocks[x][y-1][z] == AIR;
        bool frontIsAir  = currentChunk.blocks[x][y][z+1] == AIR;
        bool backIsAir   = currentChunk.blocks[x][y][z-1] == AIR;

        bool lastBlockX = (x >= CHUNK_SIZE-1);
        bool lastBlockY = (y >= CHUNK_SIZE-1);
        bool lastBlockZ = (z >= CHUNK_SIZE-1);

        bool firstBlockX = (x <= 0);
        bool firstBlockY = (y <= 0);
        bool firstBlockZ = (z <= 0);

        if (lastBlockX)
        {
            if (chunkIndex.x >= CHUNK_SIZE-1)
                rightIsAir = false;
            else
                rightIsAir = getChunk(chunkIndex.x+1, chunkIndex.y, chunkIndex.z).blocks[0][y][z] == AIR;
        }

        if (lastBlockY)
        {
            if (chunkIndex.y >= CHUNK_SIZE-1)
                topIsAir = false;
            else
                topIsAir = getChunk(chunkIndex.x, chunkIndex.y+1, chunkIndex.z).blocks[x][0][z] == AIR;
        }
            

        if (lastBlockZ)
        {
            if (chunkIndex.z >= CHUNK_SIZE-1)
                frontIsAir = false;
            else
                frontIsAir = getChunk(chunkIndex.x, chunkIndex.y, chunkIndex.z+1).blocks[x][y][0] == AIR;
        }


        if (firstBlockX)
        {
            if (chunkIndex.x <= 0)
                leftIsAir = false;
            else
                leftIsAir = getChunk(chunkIndex.x-1, chunkIndex.y, chunkIndex.z).blocks[CHUNK_SIZE-1][y][z] == AIR;
        }

        if (firstBlockY)
        {
            if (chunkIndex.y <= 0)
                bottomIsAir = false;
            else
            bottomIsAir = getChunk(chunkIndex.x, chunkIndex.y-1, chunkIndex.z).blocks[x][CHUNK_SIZE-1][z] == AIR;
        }

        if (firstBlockZ)
        {
            if (chunkIndex.z <= 0)
                backIsAir = false;
            else
                backIsAir = getChunk(chunkIndex.x, chunkIndex.y, chunkIndex.z-1).blocks[x][y][CHUNK_SIZE-1] == AIR;
        }

        bool isDrawingSide[6] = {
            (blockIsNotAir && rightIsAir), //right
            (blockIsNotAir && leftIsAir), //left
            (blockIsNotAir && topIsAir), //top
            (blockIsNotAir && bottomIsAir), //bottom
            (blockIsNotAir && frontIsAir), //front
            (blockIsNotAir && backIsAir)}; //back

        Vector3 blockPosition = (Vector3){(float)x, (float)y, (float)z};

        for (int k = 0; k < 6; k++)
            if (isDrawingSide[k])
            {
                addFaceVertices(blockPosition, k, vertices, normals, texcoords, index);
                index += 1;
            }  
    }

    verticesCount = index * SIDE_VERTICES_COUNT;
    normalsCount = index * SIDE_VERTICES_COUNT;
    texcoordsCount = index * 8;

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