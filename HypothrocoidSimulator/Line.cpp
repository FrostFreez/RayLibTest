#include "Line.h"

void Line::Draw()
{
	for (int i = 0; i < lineSegments.size(); i++)
	{
		for (int j = 0; j < lineSegments[i].segment.size() - 1; j++)
		{
			DrawLineV(lineSegments[i].segment[j], lineSegments[i].segment[j + 1], lineSegments[i].color);
		}
	}
}

void Line::AddPosition(Vector2 newPosition)
{
	lineSegments[lineSegments.size() - 1].segment.push_back(newPosition);
}

void Line::ChangeSegment(Color newColor)
{
	lineSegments.push_back({
		{lineSegments[lineSegments.size() - 1].segment[lineSegments[lineSegments.size() - 1].segment.size() - 1]},
		newColor});
	
}

void Line::Reset()
{
	LineSegment temp = {
		{lineSegments[lineSegments.size() - 1].segment[lineSegments[lineSegments.size() - 1].segment.size() - 1]},
		lineSegments[lineSegments.size() - 1].color};
	lineSegments.clear();
	lineSegments.push_back(temp);
}
