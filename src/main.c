#include "raylib.h"
#include "settings.h"
#include "world.h"
#include "player.h"

void drawDebugtext(Camera3D camera)
{
	DrawText(TextFormat("Position [x: %d, y: %d, z: %d]", 
		(int)camera.position.x, 
		(int)camera.position.y, 
		(int)camera.position.z), 3, 40, 20, WHITE);

	DrawText(TextFormat("Block [x: %d, y: %d, z: %d]: %d", 
		(int)camera.position.x  % 16, 
		(int)camera.position.y  % 16, 
		(int)camera.position.z  % 16, 
		getChunk(
			((int)camera.position.x  / 16),
			((int)camera.position.y  / 16),
			((int)camera.position.z  / 16))
		.blocks
			[((int)camera.position.x  % 16)]
			[((int)camera.position.y  % 16)]
			[((int)camera.position.z  % 16)]), 3, 60, 20, WHITE);

	DrawText(TextFormat("Chunk [x: %d, y: %d, z: %d]", 
		(int)camera.position.x / 16, 
		(int)camera.position.y / 16,
		(int)camera.position.z /16), 3, 80, 20, WHITE);
}

int main()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE);

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Rhapsodia");

	Camera3D camera = {0};
	camera.position = (Vector3){13.5f, 25.5f, 5.5f}; // Camera position
	camera.target = (Vector3){0.0f, 0.0f, 0.0f};   // Camera looking at point
	camera.up = (Vector3){0.0f, 1.0f, 0.0f};	   // Camera up vector (rotation towards target)
	camera.fovy = 60.0f;						   // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;		   // Camera projection type

	Mesh testCubeMesh = GenMeshCube(0.1, 0.1, 0.1);
	Model testCubeModel = LoadModelFromMesh(testCubeMesh);

	DisableCursor();
	SetTargetFPS(144);

	worldInit();

	// game loop
	while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		UpdateCamera(&camera, CAMERA_FREE);

		BeginDrawing();
		ClearBackground(skyColor);
		BeginMode3D(camera);

		playerUpdate(camera);

		DrawGrid(10, 1);
		DrawCube((Vector3){2, 0, 0}, 2, 0.1, 0.1, RED);
		DrawCube((Vector3){0, 2, 0}, 0.1, 2, 0.1, GREEN);
		DrawCube((Vector3){0, 0, 2}, 0.1, 0.1, 2, BLUE);

		drawChunks();

		EndMode3D();

		DrawFPS(3, 3);
		DrawRectangle(GetScreenWidth()/2-2, GetScreenHeight()/2-2, 4, 4, WHITE);

		drawDebugtext(camera);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
