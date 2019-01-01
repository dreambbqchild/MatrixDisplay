#pragma once
#include "DrawingStructs.h"
#include "MatrixCanvas.h"
#include <Magick++.h>
#include <string>

class SpriteBase
{
protected:
	Rect bounds;

	void LoadImage(Magick::Image** bmp, std::string fileName);

	virtual Color TransformColor(Color color) { return color; }
	void BaseDraw(Magick::Image* bmp, MatrixCanvas& canvas);

public:
	SpriteBase(Rect bounds);
	Point GetUpperLeft() { return bounds.UpperLeft(); }
	void SetUpperLeft(Point pt) { bounds.Point = pt; }

	bool HitTest(Rect bounds);

	virtual void Draw(MatrixCanvas& canvas) = 0;

	virtual ~SpriteBase() {}
};


class Sprite : public SpriteBase
{
private:
	Magick::Image* bmp;

	void SetPixel(Point pt, Color color);

public:
	Sprite(std::string fileName, Rect bounds);
	virtual void Draw(MatrixCanvas& canvas) { BaseDraw(bmp, canvas); }
	virtual ~Sprite();
};

template<int TAnimationFrames>
class AnimatedSprite : public SpriteBase
{
private:
	int bmpIndex;
	Magick::Image* bmps[TAnimationFrames];

protected:
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
	void NextAnimationFrame() { bmpIndex = (bmpIndex + 1) % TAnimationFrames; }

	virtual ~AnimatedSprite() 
	{
		for (auto i = 0; i < TAnimationFrames; i++)
		{
			delete bmps[i];
			bmps[i] = nullptr;
		}
	}
};