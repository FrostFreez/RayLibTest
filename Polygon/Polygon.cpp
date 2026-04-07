#include "Polygon.h"
#include <math.h>

void Polygon::AddPoint(float x, float y)
{
	points.push_back({ x, y });
}

void Polygon::Draw() {
	if (points.size() >= 3)
	{
		DrawTriangleFan(points.data(), points.size(), BLACK);
		std::vector<Vector2> opp;
		for (int i = points.size() - 1; i >= 0; i--)
		{
			opp.push_back({ points[i].x, points[i].y });
		}
		DrawTriangleFan(opp.data(), opp.size(), BLACK);
	}
	else if(points.size() == 2)
	{
		DrawLineV(points[0], points[1], BLACK);
	}
	for(Vector2 circle : points)
	{
		DrawCircleV(circle, 20, RED);
	}
}

void Polygon::Clear()
{
	points.clear();
}
