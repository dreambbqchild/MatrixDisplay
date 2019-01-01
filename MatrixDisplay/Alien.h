#pragma once
#include "DrawingStructs.h"
#include "Sprite.h"
#include "LaserBeam.h"

typedef AnimatedSprite<3> AnimatedAlien;

class Alien : public AnimatedAlien
{
private:
	bool isDeadAndGone;
	bool isOnFrontLine;
	Color alienColor;
	LaserBeam shot;

protected:
	bool CountPixelHit(Point pxPoint);

public:
	Alien(std::string fileName, int rowFromTop, int colFromLeft, Color alienColor);
	Color TransformColor(Color color);
	
	void NextAnimationFrame();

	void Draw(MatrixCanvas& canvas);
	void Move(Movement movement);

	LaserBeam* GetShot() { return &shot; };
	void SetIsOnFrontLine() { isOnFrontLine = true; }
	bool GetIsOnFrontLine() { return isOnFrontLine; }

	bool IsDead() { return bmpIndex == 2; }
	
	void TryAttack();

	virtual ~Alien();
};

