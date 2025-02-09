#include "raylib.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "noise.h"
#include "world.h"
#include "chunk.h"
#include "block.h"

int main()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(1280, 720, "Rhapsodia");

	SearchAndSetResourceDir("resources");

	Camera3D camera = {0};
	camera.position = (Vector3){5.0f, 1.7f, 0.0f}; // Camera position
	camera.target = (Vector3){0.0f, 0.0f, 0.0f};   // Camera looking at point
	camera.up = (Vector3){0.0f, 1.0f, 0.0f};	   // Camera up vector (rotation towards target)
	camera.fovy = 60.0f;						   // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;		   // Camera projection type

	Vector3 boxPosition = {0.0f, 0.0f, 0.0f};

	int chunkCount = 4;
	Chunk ch[chunkCount][chunkCount];

	for (int x = 0; x < chunkCount; x++)
		for (int z = 0; z < chunkCount; z++)
		{
			ch[x][z].position = (Vector3i){x * CHUNK_SIZE, -14, z * CHUNK_SIZE};
			fillByArray(&(ch[x][z]));
			// fillChunkDiagonal(&(ch[x][z]));
			// fillChunkRandom(&(ch[x][z]));
		}

	DisableCursor();
	SetTargetFPS(144);

	// game loop
	while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		UpdateCamera(&camera, CAMERA_FREE);

		BeginDrawing();
		ClearBackground(skyColor);
		BeginMode3D(camera);

		DrawGrid(10, 1.0f);

		for (int x = 0; x < chunkCount; x++)
			for (int z = 0; z < chunkCount; z++)
				drawChunk(ch[x][z]);

		EndMode3D();
		DrawFPS(3, 3);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
