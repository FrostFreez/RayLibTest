#include "button.h"
#include "raylib.h"

Button::Button(int px, int py, int sizeX, int sizeY, std::string text)
{
	this->positionX = px;
	this->poxitionY = py;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->text = text;
}

void Button::Draw()
{
	DrawRectangle(positionX, poxitionY, sizeX, sizeY, BLACK);
	int fontSize = sizeY * 0.8f;
	int textSize = MeasureText(text.c_str(), fontSize);
	DrawText(text.c_str(), positionX + (sizeX - textSize) / 2, poxitionY + (sizeY - fontSize) / 2, fontSize, SKYBLUE);
}

bool Button::Clicked()
{
	Vector2 mousePosition = GetMousePosition();
	if (CheckCollisionPointRec(mousePosition, { (float)positionX, (float)poxitionY, (float)sizeX, (float)sizeY }))
	{
		return true;
	}
	return false;
}
