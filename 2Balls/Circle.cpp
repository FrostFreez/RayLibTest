#include "Circle.h"

Circle::Circle(Vector2 position, float radius, Color color)
	: position(position), radius(radius), color(color)
{
}

Circle::Circle(float x, float y, float radius, Color color)
	: position({x, y}), radius(radius), color(color)
{
}

void Circle::Draw()
{
	DrawCircleV(position, radius, color);
}

void Circle::Update()
{
	position.x += velocity.x;
	position.y += velocity.y;
}