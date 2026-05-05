#include "Circle.h"
#include "raymath.h"

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

void Circle::CalculateAnchorPosition(Circle& toMove, const Circle& anchor)
{
	toMove.position = anchor.position +
		Vector2Scale(Vector2{ cosf(anchor.angle), sinf(anchor.angle) }, anchor.radius - toMove.radius);
}