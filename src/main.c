#include "raylib.h"
#include "settings.h"
#include "world.h"
#include "player.h"



int main()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE);

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Rhapsodia");

	Camera3D camera = {0};
	camera.position = (Vector3){5.0f, 1.7f, 0.0f}; // Camera position
	camera.target = (Vector3){0.0f, 0.0f, 0.0f};   // Camera looking at point
	camera.up = (Vector3){0.0f, 1.0f, 0.0f};	   // Camera up vector (rotation towards target)
	camera.fovy = 60.0f;						   // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;		   // Camera projection type

	Mesh testCubeMesh = GenMeshCube(0.1, 0.1, 0.1);
	Model testCubeModel = LoadModelFromMesh(testCubeMesh);

	DisableCursor();
	SetTargetFPS(144);

	// GenMeshCube

	worldInit();

	printf("block: %d\n", chunks[0][0].blocks[0][8][0]);

	// game loop
	while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
	{

		UpdateCamera(&camera, CAMERA_FREE);

		// GetRayCollisionBox

		

		BeginDrawing();
		ClearBackground(skyColor);
		BeginMode3D(camera);

		playerUpdate(chunks, camera);

		Vector3 testCubePosition = (Vector3) {
			camera.position.x,
			camera.position.y - 1,
			camera.position.z + 1
		};

		DrawModel(testCubeModel, testCubePosition, 1, WHITE);

		DrawGrid(10, 1);
		DrawCube((Vector3){2, 0, 0}, 2, 0.1, 0.1, RED);
		DrawCube((Vector3){0, 2, 0}, 0.1, 2, 0.1, GREEN);
		DrawCube((Vector3){0, 0, 2}, 0.1, 0.1, 2, BLUE);

		drawChunks();

		EndMode3D();
		DrawFPS(3, 3);

		// DrawLine(SCREEN_WIDTH/2-1, SCREEN_HEIGHT/2,SCREEN_WIDTH/2+1, SCREEN_HEIGHT/2, WHITE);
		// DrawLine(SCREEN_WIDTH/2, SCREEN_HEIGHT/2-1, SCREEN_WIDTH/2, SCREEN_HEIGHT/2+1, WHITE);
		DrawRectangle(SCREEN_WIDTH/2-2, SCREEN_HEIGHT/2-2, 4, 4, WHITE);

		DrawText(TextFormat("Position [x: %d, y: %d, z: %d]", (int)testCubePosition.x, (int)testCubePosition.y, (int)testCubePosition.z), 3, 40, 20, WHITE);
		DrawText(TextFormat("Block [x: %d, y: %d, z: %d]", (int)testCubePosition.x  % 16, (int)testCubePosition.y  % 16, (int)testCubePosition.z  % 16), 3, 60, 20, WHITE);
		DrawText(TextFormat("Chunk [x: %d, z: %d]", (int)testCubePosition.x / 16, (int)testCubePosition.z /16), 3, 80, 20, WHITE);

		playerDebugInfo();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
