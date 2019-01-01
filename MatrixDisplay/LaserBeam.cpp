#include "LaserBeam.h"

LaserBeam::LaserBeam(Color color, Point origin, Movement movement) : color(color), point(origin), movement(movement)
{
	if (movement == Movement::Up)
		point = Point(origin.X, origin.Y + 4);
}

void LaserBeam::Draw(MatrixCanvas& canvas)
{
	auto drawingPoint = point;

	for (auto i = 0; i < 4; i++)
	{
		if (drawingPoint.X > 0 && drawingPoint.X < 96)
			canvas.Draw(drawingPoint, color);

		drawingPoint.X++;
	}

	point = point.Move(movement, 3);
}

LaserBeam::~LaserBeam()
{
}
