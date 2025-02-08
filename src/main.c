#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "world.h"

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(1280, 720, "Blockgame");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	Camera3D camera = { 0 };
    camera.position = (Vector3){ 5.0f, 1.7f, 0.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

	Vector3 boxPosition = {0.0f, 0.0f, 0.0f};

	Chunk ch;
	ch.position = (Vector3i) {0, -14, 0};
	fillChankRandom(&ch);

	DisableCursor(); 
	SetTargetFPS(144);
	
	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		UpdateCamera(&camera, CAMERA_FREE);

		BeginDrawing();
			ClearBackground(skyColor);
			BeginMode3D(camera);
			
				// DrawCube((Vector3){0,0,0}, 1, 1, 1, RED);
				// DrawBlock((Vector3){0,0,0}, WHITE);
				DrawGrid(10, 1.0f);
				drawChunk(ch);
				
			EndMode3D();
			DrawFPS (3, 3);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
