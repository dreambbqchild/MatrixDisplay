#pragma once
#include "Sprite.h"
#include "LaserBeam.h"
#include <vector>

class Tank : public Sprite
{
private:
	bool wasHit;
	LaserBeam shots[3];
	Magick::Image* destroyed;

protected:
	bool CountPixelHit(Point pxPoint);

public:
	Tank();
	bool GetWasHit() { return wasHit; }
	void Draw(MatrixCanvas& canvas);
	void Move(Movement movement);
	void Fire();
	void AddLiveShotsTo(std::vector<LaserBeam*>& activeShots);
	virtual ~Tank();
};

