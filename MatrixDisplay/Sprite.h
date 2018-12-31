#pragma once
#include "DrawingStructs.h"
#include "MatrixCanvas.h"
#include <Magick++.h>
#include <string>

#define MAKE_PATH(f) "../../../" + f

class SpriteBase
{
protected:
	Rect bounds;

	virtual Color TransformColor(Color color) { return color; }
	void BaseDraw(Magick::Image& bmp, MatrixCanvas& canvas);

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
	Magick::Image bmp;

	void SetPixel(Point pt, Color color);

public:
	Sprite(std::string fileName, Rect bounds);
	void Draw(MatrixCanvas& canvas) { BaseDraw(bmp, canvas); }
	virtual ~Sprite() {}
};

template<int16_t TAnimationFrames>
class AnimatedSprite : public SpriteBase
{
private:
	int16_t bmpIndex;
	Magick::Image bmps[TAnimationFrames];

protected:
	void SetFrame(int16_t index, std::string fileName) 
	{
		bmps[index] = Magick::Image(MAKE_PATH(fileName));
	}

public:
	AnimatedSprite(Rect bounds) : SpriteBase(bounds) {}
	void Draw(MatrixCanvas& canvas) { BaseDraw(bmps[bmpIndex], canvas); }
	void NextAnimationFrame() { bmpIndex = (bmpIndex + 1) % TAnimationFrames; }

	virtual ~AnimatedSprite() {}
};