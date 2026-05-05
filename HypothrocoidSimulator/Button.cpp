#include "button.h"
#include "raylib.h"
#include <stdio.h>

Button::Button(int px, int py, int sizeX, int sizeY, int fontSize, std::string text)
{
	this->positionX = px;
	this->poxitionY = py;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->fontSize = fontSize;
	this->text = text;
}

void Button::SetColors(Color background, Color text)
{
	backgroundColor = background;
	textColor = text;
}

void Button::Draw()
{
	DrawRectangle(positionX, poxitionY, sizeX, sizeY, backgroundColor);
	int fontSize = this->fontSize;
	int textSize = MeasureText(text.c_str(), fontSize);
	DrawText(text.c_str(), positionX + (sizeX - textSize) / 2, poxitionY + (sizeY - fontSize) / 2, fontSize, textColor);
}

bool Button::Clicked()
{
	printf("Mouse");
	Vector2 mousePosition = GetMousePosition();
	if (CheckCollisionPointRec(mousePosition, { (float)positionX, (float)poxitionY, (float)sizeX, (float)sizeY }))
	{
		action();
		return true;
		printf("Pressed");
	}
	return false;
}
