#pragma once
#include "raylib.h"
#include <vector>
#include "raymath.h"
#include <string>
#include <array>

class WallBreaker
{
public:

#define MAX_LIVES 5
#define ROW_OF_BRICKS 2
#define BRICKS_PER_ROW 2
#define GAP 12
#define BRICK_HEIGHT 40
#define SPEED 10
#define BALL_ACCELERATION 0.01f
#define LIFE_SIZE 40

	static const int screenWidth = 1280;
	static const int screenHeight = 720;
	static const int ballStarterSpeed = 5;
	bool restart = false;

	Vector2 GetCenter(Rectangle rec)
	{
		return Vector2{rec.x + rec.width / 2, rec.y + rec.height / 2};
	}

	typedef struct Player {
		int lives;
		Color color;
		Vector2 position;
		Vector2 size;
		Rectangle GetRect() {
			return Rectangle{ position.x, position.y, size.x, size.y };
		}
		void Update() {
			float direction = 0;
			direction += IsKeyDown(KEY_LEFT) ? -1 : 0;
			direction += IsKeyDown(KEY_RIGHT) ? 1 : 0;

			position.x += direction * SPEED;

			position.x = std::max(std::min(screenWidth - size.x, position.x), 0.0f);

			DrawRectangleRounded(GetRect(), 0.2f, 8, color);
		}
		void Draw() {
			DrawRectangleRounded(GetRect(), 0.2f, 8, color);
		}
	}Player;

	typedef struct Ball {
		Vector2 position;
		float radius;
		Color color;
		bool active;
		float speed = ballStarterSpeed;
		Vector2 velocity = { 0, -speed };
		void Update()
		{
			if (active)
			{
				speed += BALL_ACCELERATION;
				velocity = Vector2Scale(Vector2Normalize(velocity), speed);
				if (position.x - radius < 0 || position.x + radius > screenWidth) {
					velocity.x *= -1;
				}
				if (position.y - radius < 0)
					velocity.y *= -1;
				position += velocity;
			}
		}
		void Draw() {
			DrawCircleV(position, radius, color);
		}
	}Ball;

	typedef struct Brick {
		Color color;
		Rectangle rect;
		bool active = true;
		void Draw()
		{
			if (active) {
				DrawRectangleRounded(rect, 0.2f, 8, this->color);
			}
		}
	}Brick;

	typedef struct Life {
		Rectangle rect;
		float borderSize;
		Color insideColor;
		Color outsideColor;
		bool active = true;
		void Draw()
		{
			DrawRectangle(rect.x, rect.y, rect.width, rect.height, outsideColor);
			DrawRectangle(rect.x + borderSize, rect.y + borderSize,
				rect.width - 2 * borderSize, rect.height - 2 * borderSize,
				active ? insideColor : BLACK);
		}
	}Life;

	typedef struct CustomScreen {
		std::string text;
		int fontSize;
		Color color;
		void Draw()
		{
			DrawRectangle(0, 0, screenWidth, screenHeight, Color{ 0,0,0, 100 });
			Vector2 textSize = Vector2{ (float)MeasureText(text.c_str(), fontSize), (float)fontSize};
			DrawText(text.c_str(), (screenWidth - textSize.x) / 2, (screenHeight - textSize.y) / 2, fontSize, color);
		}
	}CustomScreen;


	Player player;
	Ball ball;
	std::vector<Brick> bricks;

	std::array<Life, 5> lives;

	CustomScreen pauseMenu;
	CustomScreen winMenu;
	CustomScreen loseMenu;

	CustomScreen* activeScreen = nullptr;


	void Main();
	void Start();
	void Update();
};