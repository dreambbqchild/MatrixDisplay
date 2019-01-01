#include "Sprite.h"
#include <iostream>

#define MAKE_PATH(f) "../../../" + f

using namespace std;

Color black(0, 0, 0);

SpriteBase::SpriteBase(Rect bounds) : bounds(bounds)
{
}

void SpriteBase::LoadImage(Magick::Image** bmp, string fileName)
{
	*bmp = new Magick::Image();
	(*bmp)->read(MAKE_PATH(fileName));
}

bool SpriteBase::HitTest(Rect rect)
{
	bool hitDetected = false;
	for (auto row = 0; row < rect.Size.Height; row++)
	{
		for (auto col = 0; col < rect.Size.Width; col++)
		{
			auto point = Point(col + rect.Point.X, row + rect.Point.Y);
			if (bounds.PointIntersects(point))
			{
				auto pxPoint = Point(point.X - bounds.Point.X, point.Y - bounds.Point.Y);
				if (CountPixelHit(pxPoint))
					hitDetected = true;
			}
		}
	}

	return hitDetected;
}

void SpriteBase::BaseDraw(Magick::Image* bmp, MatrixCanvas& canvas)
{
	auto pixels = bmp->getPixels(0, 0, bounds.Size.Width, bounds.Size.Height);
	auto index = 0;
	for (auto row = 0; row < bounds.Size.Height; row++)
	{
		Point current = bounds.Point.Y + row;
		for (auto col = 0; col < bounds.Size.Width; col++)
		{
			Color color(ScaleQuantumToChar(pixels[index].red), ScaleQuantumToChar(pixels[index].green), ScaleQuantumToChar(pixels[index].blue));
			current.X = bounds.Point.X + col;
			color = TransformColor(color);
	
			if(color != black)
				canvas.Draw(current, color);
			
			index++;
		}
	}
}

Sprite::Sprite(string fileName, Rect bounds) : SpriteBase(bounds), bmp(nullptr)
{
	LoadImage(&bmp, fileName);
}

Sprite::~Sprite()
{
	delete bmp;
	bmp = nullptr;
}