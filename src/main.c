#include "raylib.h"
#include "world.h"

int main()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(1280, 720, "Rhapsodia");

	Camera3D camera = {0};
	camera.position = (Vector3){5.0f, 1.7f, 0.0f}; // Camera position
	camera.target = (Vector3){0.0f, 0.0f, 0.0f};   // Camera looking at point
	camera.up = (Vector3){0.0f, 1.0f, 0.0f};	   // Camera up vector (rotation towards target)
	camera.fovy = 60.0f;						   // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;		   // Camera projection type

	Vector3 boxPosition = {0.0f, 0.0f, 0.0f};

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

		DrawGrid(10, 1);
		DrawCube((Vector3){2, 0, 0}, 2, 0.1, 0.1, RED);
		DrawCube((Vector3){0, 2, 0}, 0.1, 2, 0.1, GREEN);
		DrawCube((Vector3){0, 0, 2}, 0.1, 0.1, 2, BLUE);

		drawChunks();

		EndMode3D();
		DrawFPS(3, 3);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
