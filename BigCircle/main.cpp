#include "raylib.h"
#include "Circle.h"
#include <vector>
#include "raymath.h"
#include <algorithm>
#include <iostream>

const int r = 15;

Color GenerateRandomColor()
{
	return Color{
		(unsigned char)GetRandomValue(0, 255),
		(unsigned char)GetRandomValue(0, 255),
		(unsigned char)GetRandomValue(0, 255),
		255
	};
}

static void BoundDetection(Circle& ball, std::vector<Circle>& balls)
{
	float distance = Vector2Distance(ball.position, { 400,400 }) + ball.radius;

	if (distance > 400)
	{
		Vector2 normal = Vector2Normalize(Vector2{ 400, 400 } - ball.position);
		ball.velocity = Vector2Reflect(ball.velocity, normal);
		ball.position += Vector2Scale(normal, r);
		ball.line.push_back(ball.position);
		balls.push_back(Circle(ball.position, r, GenerateRandomColor()));
		balls[balls.size() - 1].velocity = Vector2Scale(
			Vector2Rotate(normal, (float)GetRandomValue(-PI * 120, PI * 120) / 360.0f),
			GetRandomValue(5, 10));
	}
}

int main()
{
	InitWindow(800, 800, "BigBall");

	std::vector<Circle> balls = {
		Circle(200, 400, r, BLUE)
	};

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(DARKGRAY);

		DrawCircle(400, 400, 400, RAYWHITE);

		std::vector<Circle> spawns;

		for (auto& b : balls)
		{
			b.Update();
			BoundDetection(b, spawns);
		}

		for (auto& b : spawns)
		{
			balls.push_back(b);
		}

		for (auto& b : balls)
		{
			b.Draw();
		}

		EndDrawing();
	}

	CloseWindow();

	return 0;
}