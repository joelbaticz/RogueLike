#include <vector>
#include "Viewport.h"
#include "AssetManager.h"

Viewport::Viewport()
{
	SetSize(new Size(100, 100));
}

Viewport::~Viewport()
{

}

void Viewport::SetRenderedLevel(Level* renderedLevel)
{
	this->renderedLevel = renderedLevel;
}

void Viewport::Draw(GraphicsContext* g)
{
	//Render level objects separately

	g->BeginDraw();

	g->SetPenColor(AssetManager::CreateColor(255, 255, 255, 255));

	//Vertices and Indices are interogated and decided if they would go into
	//the global vertex object list to be rendered

	std::vector<Math::Vec4> drawableVerticesList;
		
	for (int i = 0; i < renderedLevel->listCubes.size(); i++)
	{
		std::vector<Math::Vec4> cubeVertices = renderedLevel->listCubes[i]->GetVertexList();

		for (Math::Vec4 cubeVertex : cubeVertices)
		{
			drawableVerticesList.push_back(cubeVertex);
		}
	}

	rotationAngleX += 0.001f;
	//if (rotationAngleX > 360) rotationAngleX = 0;
	rotationAngleY += 0.01f;
	//if (rotationAngleY > 360) rotationAngleY = 0;

	Math::Mat4 scalingMatrix;
	Math::Mat4 rotationMatrixX;
	Math::Mat4 rotationMatrixY;

	scalingMatrix.Scaling(2.5f);
	rotationMatrixX.RotationX(rotationAngleX);
	rotationMatrixY.RotationY(rotationAngleY);

	//worldMatrix *= 20.0f;// (scalingMatrix * rotationMatrixY);

	for (Math::Vec4 drawableVertex : drawableVerticesList)
	{
		drawableVertex = drawableVertex * scalingMatrix * rotationMatrixY * rotationMatrixX;
		g->DrawLine(drawableVertex.x - 1 + 400, drawableVertex.y - 1 + 300, drawableVertex.x + 1 + 400, drawableVertex.y + 1 + 300);
		g->DrawLine(drawableVertex.x + 1 + 400, drawableVertex.y - 1 + 300, drawableVertex.x - 1 + 400, drawableVertex.y + 1 + 300);
	}

	g->EndDraw();
}