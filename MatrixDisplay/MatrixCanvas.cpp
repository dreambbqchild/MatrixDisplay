#include "MatrixCanvas.h"
#include <unistd.h>
#include <exception>
#include <iostream>

using namespace std;

void MatrixCanvas::RenderLoop(MatrixCanvas* canvas)
{
	try
	{
		while (canvas->runLoop)
		{
			canvas->renderingCanvas->Clear();
			canvas->root->BeginDraw();
			canvas->renderingCanvas->Refresh();
			usleep(1000000 / canvas->fps);
		}
	}
	catch (exception& e)
	{
		cout << "Render Loop Broke: " << e.what() << endl;
	};
}

void MatrixCanvas::BeginRenderLoop(IRenderingCanvas* renderingCanvas)
{
	if (!renderLoop)
	{
		this->renderingCanvas = renderingCanvas;
		renderLoop = new std::thread(RenderLoop, this);
	}
}

void MatrixCanvas::Draw(Point& pt, Color& px)
{
	auto panelIndex = static_cast<size_t>(pt.Y / 32);
	if(panelIndex < panels.size())
		panels.at(panelIndex)->Draw(pt, px);
}

void MatrixCanvas::DrawText(Point& pt, Color& px, const char* text)
{
	auto panelIndex = static_cast<size_t>(pt.Y / 32);
	if (panelIndex < panels.size())
		panels.at(panelIndex)->DrawText(pt, px, text);
}

void MatrixCanvas::EndRenderLoop()
{
	if (runLoop && renderLoop)
	{
		runLoop = false;
		renderLoop->join();
		renderingCanvas = nullptr;
	}
}

MatrixCanvas::~MatrixCanvas()
{
	for (auto itr = panels.begin(); itr != panels.end(); itr++)
		delete *itr;

	panels.clear();

	if(renderLoop)
		delete renderLoop;
}
