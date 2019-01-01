#include "Alien.h"
#include "Random.h"

using namespace std;

Random<103> randomAttack;
Color white(255, 255, 255);

#define LEFT_FOR_64_COL_MATRIX_WITH_6_ALIENS 5

Alien::Alien(std::string fileName, int rowFromTop, int colFromLeft, Color alienColor) 
	: AnimatedSprite<2>(Rect(Point(LEFT_FOR_64_COL_MATRIX_WITH_6_ALIENS + colFromLeft * 9, (4 - rowFromTop) * 10), Size(7, 8))), isOnFrontLine(false), alienColor(alienColor), shot()
{
	SetFrame(0, fileName + "_0.png");
	SetFrame(1, fileName + "_1.png");
}

Color Alien::TransformColor(Color color)
{
	if (color.R != 0)
		return alienColor;

	return color;
}

void Alien::Draw(MatrixCanvas& canvas)
{
	AnimatedSprite<2>::Draw(canvas);

	if (shot.IsLive())
		shot.Draw(canvas);
}

void Alien::TryAttack()
{
	if (isOnFrontLine && !shot.IsLive() && randomAttack.Next() == 0)
		shot = LaserBeam(white, Point(bounds.Point.X + 3, bounds.Point.Y + 5), Movement::Down);
}

Alien::~Alien()
{
}
