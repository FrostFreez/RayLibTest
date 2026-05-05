#pragma once
#include <vector>
#include "raylib.h"
struct LineSegment
{
	std::vector<Vector2> segment;
	Color color;
};