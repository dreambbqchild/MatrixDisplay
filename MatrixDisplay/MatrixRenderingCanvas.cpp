#include "MatrixRenderingCanvas.h"
#include <iostream>

using namespace rgb_matrix;
using namespace std;

Point MatrixRenderingCanvas::TopTransformer(Point& pt)
{
	Point translated = { 0 };
	translated.X = pt.X;
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
	translated.X = pt.X + 128;
	translated.Y = pt.Y % 32;

	return translated;
}

MatrixRenderingCanvas::MatrixRenderingCanvas() : controller(), matrix(nullptr), backBuffer(nullptr)
{
	RGBMatrix::Options options;
	options.hardware_mapping = "adafruit-hat";
	options.rows = 32;
	options.cols = 64;
	options.chain_length = 3;
	options.parallel = 1;
	options.show_refresh_rate = false;

	RuntimeOptions runtime;
	runtime.drop_privileges = 0; //<-- Do as I say, don't do as I do and I say, don't do this.
	runtime.gpio_slowdown = 3;

	matrix = CreateMatrixFromOptions(options, runtime);
	
	if (!matrix)
		return;
	
	cout << "Created Matrix" << endl;

	backBuffer = matrix->CreateFrameCanvas();
	if (!backBuffer)
		return;

	cout << "Created Canvas" << endl;
}

void MatrixRenderingCanvas::Clear()
{

}

void MatrixRenderingCanvas::Draw(Point& pt, Color& color) 
{
	if (!backBuffer)
		return;

	backBuffer->SetPixel(pt.X, pt.Y, color.R, color.G, color.B);
}

void MatrixRenderingCanvas::Refresh() 
{
	if (!matrix || !backBuffer)
		return;

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

	cout << "Matrix Destructor Ran" << endl;
}
