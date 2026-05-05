#pragma once
#include <raylib.h>
#include <vector>

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
	float angle = 0;


	void Draw();

	static void CalculateAnchorPosition(Circle&, const Circle&);
};