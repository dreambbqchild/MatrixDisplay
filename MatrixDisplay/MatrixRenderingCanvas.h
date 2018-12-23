#pragma once
#include "Interfaces.h"
#include "ArcadeController.h"
#include "led-matrix.h"

class MatrixRenderingCanvas : public IRenderingCanvas
{
private:
	ArcadeController controller;
	rgb_matrix::RGBMatrix* matrix;
	rgb_matrix::FrameCanvas* backBuffer;

public:
	static Point TopTransformer(Point& pt);
	static Point MiddleTransformer(Point& pt);
	static Point BottomTransformer(Point& pt);

	MatrixRenderingCanvas();
	IController* GetCanvasController() { return &controller; }
	uint8_t MaxPanels() { return 3; };
	void Clear();
	void Draw(Point& pt, Color& color);
	void DrawText(Point& pt, Color& color, const char* text) {}
	void Refresh();
	virtual ~MatrixRenderingCanvas();
};

