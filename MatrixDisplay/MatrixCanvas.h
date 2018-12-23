#pragma once
#include "MatrixPanel.h"
#include <vector>
#include <thread>

class MatrixCanvas
{
private:
	IRootRenderable* root;
	IRenderingCanvas* renderingCanvas;
	std::vector<MatrixPanel*> panels;
	std::thread* renderLoop;
	bool runLoop;

	static void RenderLoop(MatrixCanvas* canvas);

public:
	MatrixCanvas(IRootRenderable* root) : root(root), runLoop(true), renderingCanvas(nullptr), renderLoop(nullptr) {}

	void AddPanel(MatrixPanel* panel) { panels.push_back(panel); }
	void BeginRenderLoop(IRenderingCanvas* renderingCanvas);
	void Draw(Point& pt, Color& color);
	void DrawText(Point& pt, Color& color, const char* text);
	void EndRenderLoop();

	virtual ~MatrixCanvas();
};

