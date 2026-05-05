#pragma once
#include <raylib.h>

class Circle
{
public:
	Circle() = default;
	Circle(Vector2 position, float radius, Color color);
	Circle(float x, float y, float radius, Color color);
	~Circle() = default;

	Vector2 position = {0, 0};
	float radius = 0;
	Color color = WHITE;
	Vector2 velocity = { (float)GetRandomValue(-5, 5), (float)GetRandomValue(-5, 5) };

	void Draw();

	void Update();
};