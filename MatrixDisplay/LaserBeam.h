#pragma once
#include "DrawingStructs.h"
#include "MatrixCanvas.h"

class LaserBeam
{
private:
	Color color;
	Point lastPointDrawn;
	Point point;
	Movement movement;

public:
	LaserBeam() : color(), lastPointDrawn(0, 0), point(0, 0), movement(Movement::None) {}
	LaserBeam(Color color, Point origin, Movement movement);
	
	Rect Bounds() { return Rect(lastPointDrawn, Size(1, 4)); }
	void HitATarget() { movement = Movement::None; }
	bool IsLive() { return movement != Movement::None; }
	
	void Draw(MatrixCanvas& canvas);

	virtual ~LaserBeam();
};

