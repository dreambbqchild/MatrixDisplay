#include "LaserBeam.h"

LaserBeam::LaserBeam(Color color, Point origin, Movement movement) : color(color), point(origin), movement(movement)
{
	if (movement == Movement::Up)
		point = Point(origin.X, origin.Y - 4);
}

void LaserBeam::Draw(MatrixCanvas& canvas)
{
	auto drawingPoint = point;
	auto drew = false;
	for (auto i = 0; i < 4; i++)
	{
		if (drawingPoint.Y > 0 && drawingPoint.Y < 96)
		{
			canvas.Draw(drawingPoint, color);
			drew = true;
		}
		drawingPoint.Y++;
	}

	if (!drew)
		movement = Movement::None;

	point = point.Move(movement, 3);
}

LaserBeam::~LaserBeam()
{
}
