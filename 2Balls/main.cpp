#include "raylib.h"
#include "Circle.h"
#include <vector>
#include "raymath.h"
#include <algorithm>
#include <iostream>
#include <tuple>

int main()
{
	InitWindow(800, 800, "Polygon");

	const int r = 15;

	std::vector<Circle> circles = {
		Circle(200, 400, r, BLUE),
		Circle(600, 400, r, RED)
	};

	std::vector<std::tuple<Circle, Circle>> collisions;

	

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(DARKGRAY);

		for (Circle& circle : circles)
		{
			circle.Update();
		}

		std::sort(circles.begin(), circles.end(), [](const Circle& a, const Circle& b) {
			return a.position.x < b.position.x;
			});

		for (Circle& circle : circles) {
			if (circle.position.x < r)
			{
				circle.position.x = r;
				circle.velocity.x = copysignf(GetRandomValue(3, 8), -circle.velocity.x);
			}
			else {
				break;
			}
		}

		for (int i = circles.size() - 1; i >= 0; i--) {
			if (circles[i].position.x > 800 - r)
			{
				circles[i].position.x = 800 - r;
				circles[i].velocity.x = copysignf(GetRandomValue(3, 8), -circles[i].velocity.x);
			}
			else {
				break;
			}
		}

		for (Circle& circle : circles)
		{
			if (circle.position.y - r < 0)
			{
				circle.position.y = r;
				circle.velocity.y = copysignf(GetRandomValue(3, 8), -circle.velocity.y);
			}
			else if (circle.position.y > 800 - r)
			{
				circle.position.y = 800 - r;
				circle.velocity.y = copysignf(GetRandomValue(3, 8), -circle.velocity.y);
			}
		}

		for (int i = 0; i < circles.size() - 1; i++)
		{
			Circle& circle = circles[i];
			for (int j = i+1; j < circles.size(); j++)
			{
				Circle& other = circles[j];
				if (other.position.x - circle.position.x < 2 * r)
				{
					if (other.position.x - circle.position.x > -2 * r)
					{
						if(Vector2DistanceSqr(circle.position, other.position) < 4 * r * r)
						{
							Vector2 midpoint = Vector2Lerp(circle.position, other.position, 0.5f);
							circle.velocity = Vector2Normalize(circle.position - midpoint) * 10;
							circle.position = midpoint + (circle.velocity * (r + 1));
							other.velocity = Vector2Normalize(other.position - midpoint) * 10;
							other.position = midpoint + (other.velocity * (r + 1));
							circles.push_back(Circle(midpoint, r,
								Color{
									(unsigned char)GetRandomValue(100, 255),
									(unsigned char)GetRandomValue(100, 255),
									(unsigned char)GetRandomValue(100, 255),
									(unsigned char)255
								}
							));
						}
					}
				}
				else {
					break;
				}
			}
		}

		for (Circle& circle : circles)
		{
			circle.Draw();
		}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}