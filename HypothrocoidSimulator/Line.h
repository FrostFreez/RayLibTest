#pragma once
#include "LineSegment.h"
#include <vector>
class Line
{
public:
	Line() = default;
	~Line() = default;

	std::vector<LineSegment> lineSegments = { LineSegment{{}, GOLD} };

	void Draw();

	void AddPosition(Vector2 newPosition);

	void ChangeSegment(Color newColor);

	void Reset();
};