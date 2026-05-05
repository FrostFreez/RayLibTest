#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <map>
#include "Circle.h"
#include "Line.h"
#include "Button.h"

int main()
{
	InitWindow(1500, 1000, "Polygon");

	// Big Circle
	const int bigCircleRadius = 423;
	Circle* bigCircle = new Circle(1000, 500, bigCircleRadius, DARKGRAY);
	float bigCircleAngleSpeed = 2;

	// Small Circle
	const int smallCircleRadius = 87;
	Circle* smallCircle = new Circle(0, 0, smallCircleRadius, RAYWHITE);

	// Line Position Circle
	const float linePositionRaius = 11;
	Circle* linePosition = new Circle(0, 0, linePositionRaius, GOLD);

	//Line Positions
	Line* line = new Line;

	// Set Buttons vector
	std::vector<Button*> buttons = {};

	// Change Color Buttons
	buttons.push_back(new Button(110, 210, 80, 80, 0, ""));
	buttons[buttons.size() - 1]->SetColors(GOLD, BLACK);
	buttons[buttons.size() - 1]->action = [line, linePosition]() mutable -> void
		{
			linePosition->color = GOLD;
			line->ChangeSegment(GOLD);
		};

	buttons.push_back(new Button(210, 210, 80, 80, 0, ""));
	buttons[buttons.size() - 1]->SetColors(RED, BLACK);
	buttons[buttons.size() - 1]->action = [line, linePosition]() mutable -> void
		{
			linePosition->color = RED;
			line->ChangeSegment(RED);
		};

	buttons.push_back(new Button(310, 210, 80, 80, 0, ""));
	buttons[buttons.size() - 1]->SetColors(GREEN, BLACK);
	buttons[buttons.size() - 1]->action = [line, linePosition]() mutable -> void
		{
			linePosition->color = GREEN;
			line->ChangeSegment(GREEN);
		};

	buttons.push_back(new Button(110, 310, 80, 80, 0, ""));
	buttons[buttons.size() - 1]->SetColors(SKYBLUE, BLACK);
	buttons[buttons.size() - 1]->action = [line, linePosition]() mutable -> void
		{
			linePosition->color = SKYBLUE;
			line->ChangeSegment(SKYBLUE);
		};

	buttons.push_back(new Button(210, 310, 80, 80, 0, ""));
	buttons[buttons.size() - 1]->SetColors(ORANGE, BLACK);
	buttons[buttons.size() - 1]->action = [line, linePosition]() mutable -> void
		{
			linePosition->color = ORANGE;
			line->ChangeSegment(ORANGE);
		};

	buttons.push_back(new Button(310, 310, 80, 80, 0, ""));
	buttons[buttons.size() - 1]->SetColors(PINK, BLACK);
	buttons[buttons.size() - 1]->action = [line, linePosition]() mutable -> void
		{
			linePosition->color = PINK;
			line->ChangeSegment(PINK);
		};

	// Reset Button
	Button* resetButton = new Button(100, 400, 300, 100, 50, "RESET");
	buttons.push_back(resetButton);
	resetButton->action = [line, linePosition]() mutable -> void
		{
			line->Reset();
		};

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(DARKBROWN);

		bigCircle->angle += bigCircleAngleSpeed * DEG2RAD;
		smallCircle->angle -= ((float)bigCircleRadius / smallCircleRadius) * bigCircleAngleSpeed * DEG2RAD;

		Circle::CalculateAnchorPosition(*smallCircle, *bigCircle);
		Circle::CalculateAnchorPosition(*linePosition, *smallCircle);

		if (IsMouseButtonPressed(0))
		{
			for (int i = buttons.size() - 1; i >= 0; i--)
			{
				buttons[i]->Clicked();
			}
		}

		line->AddPosition(linePosition->position);

		bigCircle->Draw();
		smallCircle->Draw();
		linePosition->Draw();
		line->Draw();

		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i]->Draw();
		}

		EndDrawing();
	}

	delete bigCircle;
	delete smallCircle;
	delete linePosition;
	delete line;

	for (int i = 0; i < buttons.size(); i++)
	{
		delete buttons[i];
	}

	CloseWindow();

	return 0;
}