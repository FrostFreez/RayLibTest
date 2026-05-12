#pragma once
#include "raylib.h"
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