#pragma once
#include <string>
#include "Polygon.h"

class Button
{
public:
	Button() = default;
	~Button() = default;

	Button(int px, int py, int sizeX, int sizeY, std::string text);

	void Draw();

	bool Clicked();

	void (*action)(Polygon&);

private:
	int positionX = 0, poxitionY = 0, sizeX = 100, sizeY = 100;
	std::string text = "";
};