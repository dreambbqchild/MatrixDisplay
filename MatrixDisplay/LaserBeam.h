#pragma once
#include "DrawingStructs.h"
#include "MatrixCanvas.h"

class LaserBeam
{
private:
	Color color;
	Point point;
	Movement movement;

public:
	LaserBeam() : color(), point(-1, -4), movement(Movement::None) {}
	LaserBeam(Color color, Point origin, Movement movement);
	bool IsLive() { return point.Y > -4 && point.Y < 96; }
	void Draw(MatrixCanvas& canvas);
	virtual ~LaserBeam();
};

