#pragma once
#include "DrawingStructs.h"
#include "MatrixCanvas.h"
#include <Magick++.h>
#include <string>
#include <vector>

class SpriteBase
{
protected:
	Rect bounds;

	void LoadImage(Magick::Image** bmp, std::string fileName);

	bool PixelHit(Magick::PixelPacket* pixels, Point pxPoint, int& index);
	virtual Color TransformColor(Color color) { return color; }
	virtual bool CountPixelHit(Point pxPoint) { return true; }
	void BaseDraw(Magick::Image* bmp, MatrixCanvas& canvas);

public:
	SpriteBase(Rect bounds);

	Rect GetBounds() { return bounds; }
	bool HitTest(Rect bounds);

	virtual void Draw(MatrixCanvas& canvas) = 0;

	virtual ~SpriteBase() {}
};


class Sprite : public SpriteBase
{
protected:
	Magick::Image* bmp;

public:
	Sprite(std::string fileName, Rect bounds);
	virtual void Draw(MatrixCanvas& canvas) { BaseDraw(bmp, canvas); }
	virtual ~Sprite();
};

template<int TAnimationFrames>
class AnimatedSprite : public SpriteBase
{
protected:
	int bmpIndex;
	Magick::Image* bmps[TAnimationFrames];

	void SetFrame(int index, std::string fileName) 
	{
		LoadImage(&bmps[index], fileName);
	}

public:
	AnimatedSprite(Rect bounds) : SpriteBase(bounds), bmpIndex(0), bmps() {}
	virtual void Draw(MatrixCanvas& canvas)
	{
		BaseDraw(bmps[bmpIndex], canvas); 
	}

	virtual void NextAnimationFrame() { bmpIndex = (bmpIndex + 1) % TAnimationFrames; }

	virtual ~AnimatedSprite() 
	{
		for (auto i = 0; i < TAnimationFrames; i++)
		{
			delete bmps[i];
			bmps[i] = nullptr;
		}
	}
};