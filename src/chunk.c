#include <mem.h>
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

    for (int i = 0; i < pow(CHUNK_SIZE, 3); i++)
    {
        int x = i % CHUNK_SIZE;
        int y = (i / CHUNK_SIZE) % CHUNK_SIZE;
        int z = i / (CHUNK_SIZE * CHUNK_SIZE);

        Vector3 blockPosition = (Vector3){(float)x, (float)y, (float)z};

        Chunk currentChunk = getChunk(chunkIndex.x, chunkIndex.y, chunkIndex.z);

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
                rightIsAir = true;
        }

        if (lastBlockY)
        {
            if (chunkIndex.y < CHUNK_SIZE-1)
                topIsAir = getChunk(chunkIndex.x, chunkIndex.y+1, chunkIndex.z).blocks[x][0][z] == AIR;
            else
                topIsAir = true;
        }

        if (lastBlockZ)
        {
                frontIsAir = true;
        }


        if (firstBlockX)
            leftIsAir = false;

        if (firstBlockY)
            bottomIsAir = false;

        if (firstBlockZ)
            backIsAir = false;

        bool isDrawingSide[6] = {
            (blockIsNotAir && rightIsAir), //right
            (blockIsNotAir && leftIsAir), //left
            (blockIsNotAir && topIsAir), //top
            (blockIsNotAir && bottomIsAir), //bottom
            (blockIsNotAir && frontIsAir), //front
            (blockIsNotAir && backIsAir)}; //back

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