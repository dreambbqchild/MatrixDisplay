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
	LaserBeam() : color(), point(0, 0), movement(Movement::None) {}
	LaserBeam(Color color, Point origin, Movement movement);
	bool IsLive() { return movement != Movement::None; }
	void Draw(MatrixCanvas& canvas);
	virtual ~LaserBeam();
};

