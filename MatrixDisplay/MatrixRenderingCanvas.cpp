#include "MatrixRenderingCanvas.h"

using namespace rgb_matrix;

Point MatrixRenderingCanvas::TopTransformer(Point& pt)
{
	Point translated = { 0 };
	translated.X = pt.X + 128;
	translated.Y = pt.Y % 32;

	return translated;
}

Point MatrixRenderingCanvas::MiddleTransformer(Point& pt)
{
	Point translated = { 0 };
	translated.X = 127 - pt.X;
	translated.Y = 31 - (pt.Y % 32);

	return translated;
}

Point MatrixRenderingCanvas::BottomTransformer(Point& pt)
{
	Point translated = { 0 };
	translated.X = pt.X;
	translated.Y = pt.Y % 32;

	return translated;
}

MatrixRenderingCanvas::MatrixRenderingCanvas() : controller()
{
	RGBMatrix::Options options;
	options.hardware_mapping = "adafruit-hat";
	options.rows = 96;
	options.cols = 64;
	options.chain_length = 3;
	options.parallel = 1;
	options.show_refresh_rate = false;

	RuntimeOptions runtime;
	runtime.drop_privileges = 1;
	runtime.gpio_slowdown = 3;

	matrix = CreateMatrixFromOptions(options, runtime);
	backBuffer = matrix->CreateFrameCanvas();
}

void MatrixRenderingCanvas::Clear()
{

}

void MatrixRenderingCanvas::Draw(Point& pt, Color& color) 
{
	backBuffer->SetPixel(pt.X, pt.Y, color.R, color.G, color.B);
}

void MatrixRenderingCanvas::Refresh() 
{
	backBuffer = matrix->SwapOnVSync(backBuffer);
	backBuffer->Clear();
}

MatrixRenderingCanvas::~MatrixRenderingCanvas()
{
	if (matrix)
	{
		matrix->Clear();
		delete matrix;
	}
}
