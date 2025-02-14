#include "raylib.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "noise.h"
#include "world.h"

#define SHADER_ON

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Rhapsodia");

	// SearchAndSetResourceDir("resources");

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

	#ifdef SHADER_ON
	Shader shader = LoadShader(0, TextFormat("resources/shaders/grayscale.fs"));
	#endif //SHADER_ON

	RenderTexture2D target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

	Vector3 position = (Vector3){0,0,0};
	// game loop
	while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
	{

	#ifdef SHADER_ON
		UpdateCamera(&camera, CAMERA_FREE);

		BeginTextureMode(target);       // Enable drawing to texture
			ClearBackground(skyColor);  // Clear texture background
            BeginMode3D(camera);        // Begin 3d mode drawing
			drawChunks();
                DrawGrid(10, 1.0f);     // Draw a grid
            EndMode3D();                // End 3d mode drawing, returns to orthographic 2d mode
        EndTextureMode(); 

		BeginDrawing();
		ClearBackground(skyColor); 

		BeginShaderMode(shader);
			DrawTextureRec(target.texture, (Rectangle){ 0, 0, (float)target.texture.width, (float)-target.texture.height }, (Vector2){ 0, 0 }, WHITE);
        EndShaderMode();

		EndShaderMode();
		EndMode3D();

		DrawFPS(3, 3);
		EndDrawing();
	#else
		UpdateCamera(&camera, CAMERA_FREE);

		BeginDrawing();
		ClearBackground(skyColor); 

		ClearBackground(skyColor);  // Clear texture background
            BeginMode3D(camera);        // Begin 3d mode drawing
			drawChunks();
                DrawGrid(10, 1.0f);     // Draw a grid
            EndMode3D();  
		EndMode3D();

		DrawFPS(3, 3);
		EndDrawing();
	#endif //SHADER_ON
		
	}

	CloseWindow();
	return 0;
}
