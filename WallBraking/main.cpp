#include "WallBreaker.h"
#include "raylib.h"

int main()
{
	InitWindow(WallBreaker::screenWidth, WallBreaker::screenHeight, "Wall Breaker");

	WallBreaker wallBreaker{};

	wallBreaker.Main();

	wallBreaker.Start();

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(DARKGRAY);

		wallBreaker.Update();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}