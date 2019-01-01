#include "Alien.h"
#include "Random.h"

using namespace std;

Random<103> randomAttack;
Color white(255, 255, 255);

#define LEFT_FOR_64_COL_MATRIX_WITH_6_ALIENS 5

Alien::Alien(std::string fileName, int rowFromTop, int colFromLeft, Color alienColor) 
	: AnimatedAlien(Rect(Point(LEFT_FOR_64_COL_MATRIX_WITH_6_ALIENS + colFromLeft * 9, (4 - rowFromTop) * 10), Size(7, 8))), isDeadAndGone(false), isOnFrontLine(false), alienColor(alienColor), shot()
{
	SetFrame(0, fileName + "_0.png");
	SetFrame(1, fileName + "_1.png");
	SetFrame(2, "dead_invader.png");
}

void Alien::NextAnimationFrame() 
{
	if(bmpIndex != 2)
		bmpIndex = (bmpIndex + 1) % 2; 
}

Color Alien::TransformColor(Color color)
{
	if (color.R != 0)
		return alienColor;

	return color;
}

bool Alien::CountPixelHit(Point pxPoint)
{
	if (bmpIndex == 2)
		return false;

	auto index = 0;
	auto pixels = bmps[bmpIndex]->getPixels(0, 0, bounds.Size.Width, bounds.Size.Height);
	auto countHit = PixelHit(pixels, pxPoint, index);

	if (countHit)
		bmpIndex = 2;

	return countHit;
}

void Alien::Move(Movement movement)
{
	if (!isDeadAndGone && ((movement == Movement::Left && bounds.Point.X > 0) 
	                    || (movement == Movement::Right && bounds.UpperRight().X < 64) 
		                || (movement == Movement::Down && bounds.LowerRight().Y < 96)))
		bounds.Point = bounds.Point.Move(movement);
}

void Alien::Draw(MatrixCanvas& canvas)
{
	if (!isDeadAndGone)
	{
		AnimatedAlien::Draw(canvas);
		isDeadAndGone = bmpIndex == 2;
	}

	if (shot.IsLive())
		shot.Draw(canvas);
}

void Alien::TryAttack()
{
	if (!isDeadAndGone && isOnFrontLine && !shot.IsLive() && randomAttack.Next() == 0)
		shot = LaserBeam(white, Point(bounds.Point.X + 3, bounds.Point.Y + 5), Movement::Down);
}

Alien::~Alien()
{
}
