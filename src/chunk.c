#include <mem.h>
#include "chunk.h"

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
    // for (int i = 0; i < pow(CHUNK_SIZE, 3); i++)
    // {
    //     int x = i % CHUNK_SIZE;
    //     int y = (i / CHUNK_SIZE) % CHUNK_SIZE;
    //     int z = i / (CHUNK_SIZE * CHUNK_SIZE);

    //     bool top    = (ch.blocks[x][y][z] != AIR && ch.blocks[x][y+1][z] == AIR && y < CHUNK_SIZE-1);
    //     bool bottom = (ch.blocks[x][y][z] != AIR && ch.blocks[x][y-1][z] == AIR && y > 0);
    //     bool front  = (ch.blocks[x][y][z] != AIR && ch.blocks[x][y][z+1] == AIR && z < CHUNK_SIZE-1);
    //     bool back   = (ch.blocks[x][y][z] != AIR && ch.blocks[x][y][z-1] == AIR && z > 0);
    //     bool right  = (ch.blocks[x][y][z] != AIR && ch.blocks[x+1][y][z] == AIR && x < CHUNK_SIZE-1);
    //     bool left   = (ch.blocks[x][y][z] != AIR && ch.blocks[x-1][y][z] == AIR && x > 0);
        
    //     Vector3 blockPosition = (Vector3){(float)x + ch.position.x,  (float)y + ch.position.y, (float)z + ch.position.z};
    // }

    Mesh mesh = { 0 };
	float vertices[SIDE_VERTICES_COUNT*6*(int)(pow(CHUNK_SIZE, 3))];
    float normals[SIDE_VERTICES_COUNT*6*(int)(pow(CHUNK_SIZE, 3))];

    printf("initial size: %d\n", SIDE_VERTICES_COUNT * 6 * (int)(pow(CHUNK_SIZE, 3)));

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
        
        // printf("----------%d-----------\n", i);
        // printf("top\t%d\n", top);
        // printf("bottom\t%d\n", bottom);
        // printf("front\t%d\n", front);
        // printf("back\t%d\n", back);
        // printf("right\t%d\n", right);
        // printf("left\t%d\n\n", left);

        // if (front)
            addFaceVertices(blockPosition, FRONT, vertices, normals, &faces);
        // if (back)
            addFaceVertices(blockPosition, BACK, vertices, normals, &faces);
        // if (top)
            addFaceVertices(blockPosition, TOP, vertices, normals, &faces);
        // if (bottom)
            addFaceVertices(blockPosition, BOTTOM, vertices, normals, &faces);
        // if (right)
            addFaceVertices(blockPosition, RIGHT, vertices, normals, &faces);
        // if (left)
            addFaceVertices(blockPosition, LEFT, vertices, normals, &faces);  
        
    }

    // addFaceVertices(ch.position, FRONT, vertices, normals, &faces);
    // addFaceVertices(ch.position, BACK, vertices, normals, &faces);
    // addFaceVertices(ch.position, TOP, vertices, normals, &faces);
    // addFaceVertices(ch.position, BOTTOM, vertices, normals, &faces);
    // addFaceVertices(ch.position, RIGHT, vertices, normals, &faces);
    // addFaceVertices(ch.position, LEFT, vertices, normals, &faces);     

    printf("faces: %d\n", faces);

    size_t size = SIDE_VERTICES_COUNT * faces * sizeof(float);

    mesh.vertices = malloc(size);
    memcpy(mesh.vertices, vertices, size);

    mesh.indices = malloc(size);

    printf("mesh.vertices size: %d\n", 24*3*sizeof(float));
    printf("mesh.indices size: %d\n", 36*sizeof(unsigned short));

    printf("mesh.vertices supposed size: %d\n", size);
    printf("mesh.indices supposed size: %d\n", faces * SIDE_VERTICES_COUNT);

    int k = 0;

    for (int i = 0; i < faces * SIDE_VERTICES_COUNT; i += 6)
    {
        mesh.indices[i] = 4*k;
        mesh.indices[i + 1] = 4*k + 1;
        mesh.indices[i + 2] = 4*k + 2;
        mesh.indices[i + 3] = 4*k;
        mesh.indices[i + 4] = 4*k + 2;
        mesh.indices[i + 5] = 4*k + 3;

        k++;
    }

    mesh.vertexCount = SIDE_VERTICES_COUNT * faces;
    mesh.triangleCount = faces*2;

    // Upload vertex data to GPU (static mesh)
    UploadMesh(&mesh, false);

    return mesh;
}