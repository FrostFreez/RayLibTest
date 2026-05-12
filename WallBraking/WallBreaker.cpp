#include "WallBreaker.h"

void WallBreaker::Main()
{
}

void WallBreaker::Start()
{
#pragma region BRICKS

	float brickWidth = (screenWidth - GAP * BRICKS_PER_ROW) / BRICKS_PER_ROW;
	Vector2 size = { brickWidth, BRICK_HEIGHT };

	for (int i = 0; i < ROW_OF_BRICKS; i++)
	{
		for (int j = 0; j < BRICKS_PER_ROW; j++)
		{
			float x = (1 + j) * GAP + j * brickWidth;
			float y = (1 + i) * GAP + i * BRICK_HEIGHT;
			Rectangle rect = Rectangle{ x, y, size.x, size.y };

			Brick newBrick = Brick{ RED, rect };

			bricks.push_back(newBrick);
		}
	}

#pragma endregion

#pragma region PLAYER

	player = Player{};
	player.lives = MAX_LIVES;
	player.size = size;
	player.position.x = (screenWidth - player.size.x) / 2;
	player.position.y = screenHeight - player.size.y - GAP;
	player.color = SKYBLUE;

#pragma endregion

#pragma region BALL

	ball = Ball{};
	ball.radius = 15;
	ball.color = WHITE;


#pragma endregion

#pragma region Lives

	for (int i = 0; i < life.size(); i++)
	{
		life[i].borderSize = 5;
		life[i].rect = Rectangle{(float)GAP, (float)(screenHeight - LIFE_SIZE - GAP) - (GAP + LIFE_SIZE) * i, LIFE_SIZE, LIFE_SIZE};
		life[i].outsideColor = SKYBLUE;
		life[i].insideColor = GREEN;
	}

#pragma endregion

#pragma region CUSTOM_SCREENS

	pauseMenu = CustomScreen{ "Paused", 100, SKYBLUE };
	winMenu = CustomScreen{ "Won", 100, SKYBLUE };
	loseMenu = CustomScreen{ "Lost", 100, SKYBLUE };

#pragma endregion
}

void WallBreaker::Update()
{
	if (activeScreen)
	{
		if (IsKeyPressed(KEY_ENTER))
		{
			activeScreen = nullptr;
		}
	}
	else
	{
		if (restart)
		{
			restart = false;

			ball.active = false;

			for (int i = 0; i < bricks.size(); i++)
			{
				bricks[i].active = true;
			}
			player.position.x = (screenWidth - player.size.x) / 2;
		}

		if (IsKeyPressed(KEY_ENTER))
		{
			activeScreen = &pauseMenu;
		}

		player.Update();

		if (ball.active)
		{
			if (CheckCollisionCircleRec(ball.position, ball.radius, player.GetRect()))
			{
				ball.velocity = Vector2Normalize(ball.position - GetCenter(player.GetRect())) * ball.speed;
			}
		}
		else {
			ball.position.x = player.position.x + player.size.x / 2;
			ball.position.y = player.position.y - ball.radius;
			if (IsKeyPressed(KEY_SPACE)) {
				ball.active = true;
			}
		}

		ball.Update();

		bool broke = false;

		for (int i = 0; i < bricks.size(); i++)
		{
			if (!bricks[i].active) continue;
			if (CheckCollisionCircleRec(ball.position, ball.radius, bricks[i].rect))
			{
				bricks[i].active = false;
				ball.position -= ball.velocity;
				if (ball.position.x - ball.radius < bricks[i].rect.x + bricks[i].rect.width && ball.position.x + ball.radius > bricks[i].rect.x)
				{
					ball.velocity.y *= -1;
				}
				else if (ball.position.y - ball.radius < bricks[i].rect.y + bricks[i].rect.height && ball.position.y + ball.radius > bricks[i].rect.y)
				{
					ball.velocity.x *= -1;
				}
				broke = true;
				break;
			}
		}

		bool hasLeft = false;

		for (int i = 0; i < bricks.size(); i++)
		{
			if (bricks[i].active) {
				hasLeft = true;
				break;
			}
		}

		if (!hasLeft)
		{
			activeScreen = &winMenu;
			restart = true;
		}

		if (ball.position.y > screenHeight + ball.radius)
		{
			ball.active = false;
			ball.velocity.x = 0;
			ball.velocity.y = -ballStarterSpeed;
			player.lives -= 1;
			if (player.lives <= 0)
			{
				activeScreen = &loseMenu;
				restart = true;
			}
			for (int i = 0; i < life.size(); i++)
			{
				if (i < player.lives)
				{
					life[i].active = true;
				}
				else
				{
					life[i].active = false;
				}
			}
		}
	}



	for (Brick& b : bricks) {
		b.Draw();
	}
	ball.Draw();
	player.Draw();
	if (activeScreen)
	{
		activeScreen->Draw();
	}
	for (Life& l : life)
	{
		l.Draw();
	}
}