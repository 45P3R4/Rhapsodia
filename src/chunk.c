#include <mem.h>
#include "chunk.h"

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
        ch->blocks[i % CHUNK_SIZE][(i / CHUNK_SIZE) % CHUNK_SIZE][i / (CHUNK_SIZE * CHUNK_SIZE)] = blockType;
    }
}


Mesh genMeshChunk(Chunk ch)
{
    Mesh mesh = {0};
    mesh.vboId = (unsigned int *)RL_CALLOC(MAX_MESH_VBO, sizeof(unsigned int));

    float *vertices = RL_MALLOC(36 * 3 * CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * sizeof(float));
    float *texcoords = RL_MALLOC(36 * 2 * CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * sizeof(float));
    float *normals = RL_MALLOC(36 * 3 * CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * sizeof(float));

    int verticesCount = 0;
    int texcoordsCount = 0;
    int normalsCount = 0;

    for (int i = 0; i < pow(CHUNK_SIZE, 3); i++)
    {
        int x = i % CHUNK_SIZE;
        int y = (i / CHUNK_SIZE) % CHUNK_SIZE;
        int z = i / (CHUNK_SIZE * CHUNK_SIZE);

        bool top    = (ch.blocks[x][y][z] != AIR && ch.blocks[x][y+1][z] == AIR && y < CHUNK_SIZE-1);
        bool bottom = (ch.blocks[x][y][z] != AIR && ch.blocks[x][y-1][z] == AIR && y > 0);
        bool front  = (ch.blocks[x][y][z] != AIR && ch.blocks[x][y][z+1] == AIR && z < CHUNK_SIZE-1);
        bool back   = (ch.blocks[x][y][z] != AIR && ch.blocks[x][y][z-1] == AIR && z > 0);
        bool right  = (ch.blocks[x][y][z] != AIR && ch.blocks[x+1][y][z] == AIR && x < CHUNK_SIZE-1);
        bool left   = (ch.blocks[x][y][z] != AIR && ch.blocks[x-1][y][z] == AIR && x > 0);

        if (top || bottom || front || back || right ||left)
        {
            verticesCount += 36 * 3;
            texcoordsCount += 36 * 2;
            normalsCount += 36 * 3;
        }
    }

    int faces = 0;

    Vector3 pos = {3,0,0};

    for (int i = 0; i < pow(CHUNK_SIZE, 3); i++)
    {
        int x = i % CHUNK_SIZE;
        int y = (i / CHUNK_SIZE) % CHUNK_SIZE;
        int z = i / (CHUNK_SIZE * CHUNK_SIZE);

        Vector3 blockPosition = (Vector3){(float)x + ch.position.x,  (float)y + ch.position.y, (float)z + ch.position.z};

        bool top    = (ch.blocks[x][y][z] != AIR && ch.blocks[x][y+1][z] == AIR && y < CHUNK_SIZE-1);
        bool bottom = (ch.blocks[x][y][z] != AIR && ch.blocks[x][y-1][z] == AIR && y > 0);
        bool front  = (ch.blocks[x][y][z] != AIR && ch.blocks[x][y][z+1] == AIR && z < CHUNK_SIZE-1);
        bool back   = (ch.blocks[x][y][z] != AIR && ch.blocks[x][y][z-1] == AIR && z > 0);
        bool right  = (ch.blocks[x][y][z] != AIR && ch.blocks[x+1][y][z] == AIR && x < CHUNK_SIZE-1);
        bool left   = (ch.blocks[x][y][z] != AIR && ch.blocks[x-1][y][z] == AIR && x > 0);

        if (front)
            addFaceVertices(blockPosition, FRONT, vertices, normals, texcoords, &faces);
        if (back)
            addFaceVertices(blockPosition, BACK, vertices, normals, texcoords, &faces);
        if (top)
            addFaceVertices(blockPosition, TOP, vertices, normals, texcoords, &faces);
        if (bottom)
            addFaceVertices(blockPosition, BOTTOM, vertices, normals, texcoords, &faces);
        if (right)
            addFaceVertices(blockPosition, RIGHT, vertices, normals, texcoords, &faces);
        if (left)
            addFaceVertices(blockPosition, LEFT, vertices, normals, texcoords, &faces);  
        
    }

    mesh.vertices = (float *)RL_MALLOC(verticesCount * sizeof(float));
    memcpy(mesh.vertices, vertices, verticesCount * sizeof(float));

    mesh.texcoords = (float *)RL_MALLOC(texcoordsCount * sizeof(float));
    memcpy(mesh.texcoords, texcoords, texcoordsCount * sizeof(float));

    mesh.normals = (float *)RL_MALLOC(normalsCount * sizeof(float));
    memcpy(mesh.normals, normals, normalsCount * sizeof(float));

    mesh.vertexCount = verticesCount / 3;         // fixme: Why divide by 3 ???
    mesh.triangleCount = (verticesCount / 3) / 2; // fixme: Why divide by 3 and 2 ???

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