#pragma once
#include <vector>
#include "raylib.h"

class Polygon
{
public:
	Polygon() = default;
	~Polygon() = default;

	void AddPoint(float x, float y);

	void Draw();

	void Clear();

private:
	std::vector<Vector2> points = {};
};