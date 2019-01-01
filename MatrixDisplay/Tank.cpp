#include "Tank.h"
#include "string.h"
using namespace std;

Color hotPink(248, 24, 148);
Tank::Tank() : Sprite("tank.png", Rect(Point(24, 96 - 8), Size(15, 8))), shots()
{

}

void Tank::Draw(MatrixCanvas& canvas)
{
	Sprite::Draw(canvas);

	for (auto i = 0; i < 3; i++)
	{
		if (shots[i].IsLive())
			shots[i].Draw(canvas);
	}
}

void Tank::Move(Movement movement)
{
	if ((movement == Movement::Left && bounds.Point.X > 0) || (movement == Movement::Right && bounds.UpperRight().X < 63))
		bounds.Point = bounds.Point.Move(movement);
}

bool Tank::Fire()
{
	for (auto i = 0; i < 3; i++)
	{
		if (!shots[i].IsLive())
		{
			shots[i] = LaserBeam(hotPink, Point(bounds.Point + 7, 8), Movement::Up);
			return true;
		}
	}

	return false;
}

Tank::~Tank()
{
}
