#include "raylib.h"
#include <vector>
#include "button.h"
#include "Polygon.h"

int main()
{
	InitWindow(800, 600, "Polygon");

	Button button(500, 450, 200, 50, "Click Me");
	Polygon polygon;

	button.action = [](Polygon &polygon) {
		polygon.Clear();
		printf("Button Clicked!\n");
	};

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			if (button.Clicked()) {
				button.action(polygon);
			}else{
				polygon.AddPoint(GetMouseX(), GetMouseY());
			}
		}

		polygon.Draw();
		button.Draw();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}