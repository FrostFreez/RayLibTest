#include "raylib.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

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
	float x = 0, y = 0, radius = 100;
	Color color = RED;

public:
	Circle(float x, float y, float radius, Color color) : x(x), y(y), radius(radius), color(color) {}
	void Draw()
	{
		DrawCircle(x, y, radius, color);
	}

	bool Click()
	{
		Vector2 mousePos = GetMousePosition();
		return (mousePos.x - x) * (mousePos.x - x) + (mousePos.y - y) * (mousePos.y - y) <= radius * radius;
	}

	void Move(int x, int y)
	{
		this->x += x;
		this->y += y;
	}
	void Move(Vector2 move)
	{
		this->x += move.x;
		this->y += move.y;
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
	InitWindow(800, 800, "Hello Raylib!");

	Circle circles[3] = {
		Circle(GetScreenWidth() / 2, GetScreenHeight() / 2 - 50 * sqrt(3), 20, RED),
		Circle(GetScreenWidth() / 2 - 50, GetScreenHeight() / 2, 20, GREEN),
		Circle(GetScreenWidth() / 2 + 50, GetScreenHeight() / 2, 20, BLUE)
	};
	Circle* focusedCircle = nullptr;
	Vector2 direction = { 1, 1 };
	Vector2 reverseCooldown = { 0, 0 };

	std::vector<Circle*> circlesPtr = {};

	std::vector<Circle*> trail = {};
	int frameCount = 0;
	int maxTrailLength = 134;
	trail.resize(maxTrailLength);

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		reverseCooldown.x -= 1;
		reverseCooldown.y -= 1;

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			bool clickedOnCircle = false;
			for (int i = 0; i < 3; i++) {
				if (circles[i].Click() && focusedCircle != &circles[i]) {
					focusedCircle = &circles[i];
					clickedOnCircle = true;
					break;
				}
			}
			if (!clickedOnCircle) {
				focusedCircle = nullptr;
			}
		}
		if (focusedCircle != nullptr) {

			if (GetScreenWidth() - focusedCircle->x < focusedCircle->radius || focusedCircle->x < focusedCircle->radius
				&& reverseCooldown.x <= 0) {
				direction.x = copysignf(GetRandomValue(3, 8), -direction.x);
				Color newColor = Color();
				newColor.r = GetRandomValue(0, 255);
				newColor.g = GetRandomValue(0, 255);
				newColor.b = GetRandomValue(0, 255);
				newColor.a = 255;
				circlesPtr.push_back(new Circle(focusedCircle->x, focusedCircle->y, focusedCircle->radius, newColor));
				focusedCircle = circlesPtr[circlesPtr.size() - 1];
				reverseCooldown.x = 10;
			}
			if (GetScreenHeight() - focusedCircle->y < focusedCircle->radius || focusedCircle->y < focusedCircle->radius
				&& reverseCooldown.y <= 0) {
				direction.y = copysignf(GetRandomValue(3, 8), -direction.y);
				Color newColor = Color();
				newColor.r = GetRandomValue(0, 255);
				newColor.g = GetRandomValue(0, 255);
				newColor.b = GetRandomValue(0, 255);
				newColor.a = 255;
				circlesPtr.push_back(new Circle(focusedCircle->x, focusedCircle->y, focusedCircle->radius, newColor));
				focusedCircle = circlesPtr[circlesPtr.size() - 1];
				reverseCooldown.y = 10;
			}

			if (trail[frameCount])
			{
				delete trail[frameCount];
				trail[frameCount] = nullptr;
			}

			trail[frameCount] = new Circle(focusedCircle->x, focusedCircle->y, focusedCircle->radius, focusedCircle->color);
			frameCount = (frameCount + 1) % maxTrailLength;

			focusedCircle->Move(direction);
		}

		std::vector<Vector2> vertices = {
			{ circles[0].x, circles[0].y },
			{ circles[1].x, circles[1].y },
			{ circles[2].x, circles[2].y }
		};

		DrawTriangle({ circles[0].x, circles[0].y }, { circles[1].x, circles[1].y }, { circles[2].x, circles[2].y }, BLACK);

		for (auto& circle : circles)
		{
			circle.Draw();
		}

		for (auto& circlePtr : circlesPtr)
		{
			circlePtr->Draw();
		}

		for (int i = 0; i < maxTrailLength; i++) {
			if (trail[i] != nullptr && trail[i]->radius > 0.1f) {
				trail[i]->Draw();
				trail[i]->radius -= 0.15f;
			}
			else {
				delete trail[i];
				trail[i] = nullptr;
			}
		}

		EndDrawing();

	}
	for (int i = 0; i < circlesPtr.size(); i++) {
		delete circlesPtr[i];
	}
	circlesPtr.clear();

	CloseWindow();

	return 0;
}