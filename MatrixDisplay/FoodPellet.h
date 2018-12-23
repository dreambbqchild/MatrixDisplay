#pragma once
#include "MatrixCanvas.h"
#include "SnakeGameField.h"

class FoodPellet
{
private:
	Point upperLeft;
	Color color;

public:
	FoodPellet(SnakeGameField& gameField);

	Point GetUpperLeftPoint() { return upperLeft; }

	void Draw(MatrixCanvas& canvas);
};