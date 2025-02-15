#include "raylib.h"
#include "world.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Rhapsodia");

	Camera3D camera = {0};
	camera.position = (Vector3){5.0f, 1.7f, 0.0f}; // Camera position
	camera.target = (Vector3){0.0f, 0.0f, 0.0f};   // Camera looking at point
	camera.up = (Vector3){0.0f, 1.0f, 0.0f};	   // Camera up vector (rotation towards target)
	camera.fovy = 60.0f;						   // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;		   // Camera projection type

	DisableCursor();
	SetTargetFPS(144);

	// GenMeshCube

	worldInit();

	// game loop
	while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
	{

		UpdateCamera(&camera, CAMERA_FREE);

		BeginDrawing();
		ClearBackground(skyColor);
		BeginMode3D(camera);

		DrawGrid(10, 1);
		DrawCube((Vector3){2, 0, 0}, 2, 0.1, 0.1, RED);
		DrawCube((Vector3){0, 2, 0}, 0.1, 2, 0.1, GREEN);
		DrawCube((Vector3){0, 0, 2}, 0.1, 0.1, 2, BLUE);

		drawChunks();

		EndMode3D();
		DrawFPS(3, 3);
		DrawText("v0.0.1 dev", SCREEN_WIDTH - 50, SCREEN_HEIGHT - 20, 10, WHITE);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
