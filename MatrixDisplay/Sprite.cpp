#include "Sprite.h"

SpriteBase::SpriteBase(Rect bounds) : bounds(bounds)
{
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

void SpriteBase::BaseDraw(Magick::Image& bmp, MatrixCanvas& canvas)
{
	auto pixels = bmp.getPixels(0, 0, bounds.Size.Width, bounds.Size.Height);
	auto index = 0;
	for (auto row = 0; row < bounds.Size.Width; row++)
	{
		Point current = bounds.Point.Y + row;
		for (auto col = 0; col < bounds.Size.Height; col++)
		{
			Color color(ScaleQuantumToChar(pixels[index].red), ScaleQuantumToChar(pixels[index].green), ScaleQuantumToChar(pixels[index].blue));
			current.X = bounds.Point.X + col;
			color = TransformColor(color);
			canvas.Draw(current, color);
			index++;
		}
	}
}

Sprite::Sprite(std::string fileName, Rect bounds) : SpriteBase(bounds), bmp(MAKE_PATH(fileName))
{
}

void Sprite::SetPixel(Point pt, Color color)
{
	auto index = pt.Y * bounds.Size.Width + pt.X;

	auto pixels = bmp.getPixels(0, 0, bounds.Size.Width, bounds.Size.Height);
	pixels[index].red = ScaleToQuantum(color.R);
	pixels[index].green = ScaleToQuantum(color.G);
	pixels[index].blue = ScaleToQuantum(color.B);
	
	bmp.syncPixels();
}