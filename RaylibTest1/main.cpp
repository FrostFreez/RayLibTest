#include "raylib.h"
#include <iostream>
#include <string>

void static DisplayName(std::string name, int fontSize, Vector2 center)
{
	DrawText(name.c_str(), (center.x - MeasureText(name.c_str(), fontSize)) / 2,
		center.y - fontSize / 2, fontSize, BLACK);
}

void static DrawTest()
{
	Vector2 screenSize = { GetScreenWidth(), GetScreenHeight() };

	Vector2 rectSize = { 222, 234 };
	DrawRectangle((screenSize.x - rectSize.x) / 2, (screenSize.y - rectSize.y) / 2,
		rectSize.x, rectSize.y, BLUE);

	float polygonRadius = 100;
	DrawPoly({ screenSize.x / 2, screenSize.y / 2 },
		8, polygonRadius, 0, GREEN);


	Vector2 lineSize = { 50, 0 };
	DrawLine((screenSize.x - lineSize.x) / 2, (screenSize.y - lineSize.y) / 2,
		(screenSize.x + lineSize.x) / 2, (screenSize.y + lineSize.y) / 2, RED);
}

void static DisplayMousePosition() {
	Vector2 mousePos = GetMousePosition();
	std::string mousePosText = "Mouse Position: (" + std::to_string((int)mousePos.x) + ", " + std::to_string((int)mousePos.y) + ")";
	DisplayName(mousePosText, 100, GetMousePosition());
}

void static SwitchWindowMode() {
	if (IsWindowFullscreen()) {
		ToggleFullscreen();
	}
	else {
		ToggleBorderlessWindowed();
	}
}

class Circle
{
public:
	int x = 0, y = 0, radius = 100;
	Color color = RED;

private:
	bool focused = false;

public:
	Circle(int x, int y, int radius, Color color) : x(x), y(y), radius(radius), color(color) {}

	void Draw()
	{
		DrawCircle(x, y, radius, color);
	}

	void Click()
	{
		Vector2 mousePos = GetMousePosition();
		if (focused) {
			focused = false;
		}
		else {
			focused = (mousePos.x - x) * (mousePos.x - x) + (mousePos.y - y) * (mousePos.y - y) <= radius * radius;
		}
	}

	void Update()
	{
		Vector2 mouseDelta = GetMouseDelta();
		if (focused) {
			x += mouseDelta.x;
			y += mouseDelta.y;
		}
	}
};

void static BlendColor(Circle circles[3])
{
	BeginBlendMode(BLEND_ADDITIVE);
	for (int i = 0; i < 3; i++) {
		circles[i].Draw();
	}
	EndBlendMode();
}

int main()
{
	InitWindow(800, 450, "Hello Raylib!");

	Circle circles[3] = {
		Circle(GetScreenWidth() / 2, GetScreenHeight() / 2 - 50 * sqrt(3), 100, RED),
		Circle(GetScreenWidth() / 2 - 50, GetScreenHeight() / 2, 100, GREEN),
		Circle(GetScreenWidth() / 2 + 50, GetScreenHeight() / 2, 100, BLUE)
	};

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			for (int i = 0; i < 3; i++) {
				circles[i].Click();
			}
		}
		for (int i = 0; i < 3; i++) {
			circles[i].Update();
		}
		BlendColor(circles);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}