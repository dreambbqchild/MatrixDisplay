#include "Tank.h"
#include "string.h"
#include <iostream>
using namespace std;

Color hotPink(248, 24, 148);
Tank::Tank() : Sprite("tank.png", Rect(Point(24, 96 - 8), Size(15, 8))), wasHit(false), shots()
{
	LoadImage(&destroyed, "tank_destroyed.png");
}

bool Tank::CountPixelHit(Point pxPoint)
{
	if (wasHit)
		return false;

	auto index = 0;
	auto pixels = bmp->getPixels(0, 0, bounds.Size.Width, bounds.Size.Height);
	wasHit = PixelHit(pixels, pxPoint, index);

	return wasHit;
}

void Tank::Draw(MatrixCanvas& canvas)
{
	if (wasHit)
		BaseDraw(destroyed, canvas);
	else
		Sprite::Draw(canvas);

	for (auto i = 0; i < 3; i++)
	{
		if (shots[i].IsLive())
			shots[i].Draw(canvas);
	}
}

void Tank::Move(Movement movement)
{
	if (!wasHit && ((movement == Movement::Left && bounds.Point.X > 0) || (movement == Movement::Right && bounds.UpperRight().X < 64)))
		bounds.Point = bounds.Point.Move(movement);
}

void Tank::Fire()
{
	if (wasHit)
		return;

	for (auto i = 0; i < 3; i++)
	{
		if (!shots[i].IsLive())
		{
			shots[i] = LaserBeam(hotPink, Point(bounds.Point.X + 7, 96 - 8), Movement::Up);
			return;
		}
	}
}

void Tank::AddLiveShotsTo(std::vector<LaserBeam*>& activeShots)
{
	for (auto i = 0; i < 3; i++)
	{
		if (shots[i].IsLive())
			activeShots.push_back(&shots[i]);
	}
}

Tank::~Tank()
{
	delete destroyed;
	destroyed = nullptr;
}
