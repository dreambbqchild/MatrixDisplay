#include "Sprite.h"
#include <iostream>

#define MAKE_PATH(f) "../../../" + f

using namespace std;

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
	for (auto row = 0; row < rect.Size.Height; row++)
	{
		for (auto col = 0; col < rect.Size.Width; row++)
		{
			if (bounds.PointIntersects(Point(col + rect.Point.X, row + rect.Point.Y)))
				return true;
		}
	}

	return false;
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
			canvas.Draw(current, color);
			index++;
		}
	}
}

Sprite::Sprite(string fileName, Rect bounds) : SpriteBase(bounds), bmp(nullptr)
{
	LoadImage(&bmp, fileName);
}

void Sprite::SetPixel(Point pt, Color color)
{
	auto index = pt.Y * bounds.Size.Width + pt.X;

	auto pixels = bmp->getPixels(0, 0, bounds.Size.Width, bounds.Size.Height);
	pixels[index].red = ScaleToQuantum(color.R);
	pixels[index].green = ScaleToQuantum(color.G);
	pixels[index].blue = ScaleToQuantum(color.B);
	
	bmp->syncPixels();
}

Sprite::~Sprite()
{
	delete bmp;
	bmp = nullptr;
}