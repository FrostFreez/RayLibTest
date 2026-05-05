#pragma once
#include <string>
#include <functional>
#include "raylib.h"

class Button
{
public:
	Button() = default;
	~Button() = default;

	Button(int, int, int, int, int, std::string);
	void SetColors(Color background, Color text);

	void Draw();

	bool Clicked();

	std::function<void()> action;

	int positionX = 0, poxitionY = 0, sizeX = 100, sizeY = 100, fontSize = 100;
	std::string text = "";
	Color backgroundColor = BLACK, textColor = SKYBLUE;
};