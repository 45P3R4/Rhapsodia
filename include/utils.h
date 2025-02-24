#ifndef UTILS
#define UTILS

#define VECTOR3_RIGHT (Vector3){1,0,0}
#define VECTOR3_LEFT (Vector3){-1,0,0}
#define VECTOR3_UP (Vector3){0,1,0}
#define VECTOR3_DOWN (Vector3){0,-1,0}
#define VECTOR3_FORWARD (Vector3){0,0,1}
#define VECTOR3_BACK (Vector3){0,0,-1}

// #include "raylib.h"

typedef struct Vector3i {
    int x;
    int y;
    int z;
} Vector3i;

// Vector3i addVector3i(Vector3i vector, Vector3i additionalVector)
// {
//     Vector3i newVector = {
//         vector.x + additionalVector.x,
//         vector.y + additionalVector.y,
//         vector.z + additionalVector.z
//     };

//     return newVector;
// }

// Vector3 addVector3(Vector3 vector, Vector3 additionalVector)
// {
//     Vector3 newVector = {
//         vector.x + additionalVector.x,
//         vector.y + additionalVector.y,
//         vector.z + additionalVector.z
//     };

//     return newVector;
// }

#endif /* UTILS */
