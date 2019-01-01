#include "Bunker.h"

#define LEFT_FOR_64_COL_MATRIX_WITH_4_BUNKERS 4
                                                                                                                     //Tank Height 8 + Bunker Height 11 = 19
Bunker::Bunker(int index) : Sprite("bunker.png", Rect(Point(LEFT_FOR_64_COL_MATRIX_WITH_4_BUNKERS + index * 14, 96 - 19), Size(12, 11)))
{
}

bool Bunker::CountPixelHit(Point pxPoint)
{
	auto index = pxPoint.Y * bounds.Size.Width + pxPoint.X;
	auto pixels = bmp->getPixels(0, 0, bounds.Size.Width, bounds.Size.Height);
	auto countHit = pixels[index].red || pixels[index].green || pixels[index].blue;

	if (countHit)
	{
		pixels[index].red = pixels[index].green = pixels[index].blue = ScaleToQuantum(0);
		bmp->syncPixels();
	}

	return countHit;
}

Bunker::~Bunker()
{
}
