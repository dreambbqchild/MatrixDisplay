#include "FoodPellet.h"

FoodPellet::FoodPellet(SnakeGameField& field) : upperLeft(), color(150, 75, 0)
{
	//When this gets eaten, the point becomes part of the snake. So no need to return;
	upperLeft = field.GetRandomOpenPoint();
}

void FoodPellet::Draw(MatrixCanvas& canvas)
{
	auto workingPoint = upperLeft;

	workingPoint.X += 1;
	canvas.Draw(workingPoint, color);

	workingPoint.Y += 2;
	canvas.Draw(workingPoint, color);

	workingPoint.X -= 1;
	workingPoint.Y -= 1;
	canvas.Draw(workingPoint, color);

	workingPoint.X += 2;
	canvas.Draw(workingPoint, color);
}