#include <vector>
#include <list>
#include "Viewport.h"
#include "AssetManager.h"
#include "RendererFront.h"

Viewport::Viewport(): ControlNode("Viewport")
{
	//cameraRotationX = Math::DegreeToRadian(25.0f);
	//cameraRotationY = Math::DegreeToRadian(45.0f);
	//cameraRotationZ = Math::DegreeToRadian(180.0f);
	//cameraScaling = 1.0f;

	screenWidth = (float)RendererFront::GetWindowWidth();
	screenHeight = (float)RendererFront::GetWindowHeight();
	texture = AssetManager::CreateTextureAtlas("TestTexture3.png");

	EventManager::Subscribe(this);
}

Viewport::~Viewport()
{

}

void Viewport::Update()
{
	renderedLevel->UpdateState();
}

void Viewport::SetCamera(Camera3D* camera)
{
	this->camera = camera;
}

void Viewport::SetRenderedLevel(Level* renderedLevel)
{
	this->renderedLevel = renderedLevel;
}

void Viewport::DisplayDrawError(GraphicsContext* g)
{
	g->BeginDraw();

	g->SetPenColor(statsForegroundColor);

	if (camera == nullptr)
	{
		g->DrawText("No Camera set.", AssetManager::GetDefaultFont(), 10, 10);
	}
	else
	{
		g->DrawText("No RenderedLevel set.", AssetManager::GetDefaultFont(), 10, 10);
	}

	g->EndDraw();
}

void Viewport::DisplayLevel(GraphicsContext* g)
{
	Mat4& viewMatrix = camera->GetViewMatrix();
	Mat4& projMatrix = camera->GetProjection();

	DrawMode drawMode = DrawMode::Textured;
	std::vector<Triangle> drawableTriangles;

	//for (int i = 0; i < 1; i++)
	for (int i = 0; i < renderedLevel->objectList.size(); i++)
	{
		//PER OBJECT
		LevelObject* object = renderedLevel->objectList[i];

		if (drawMode.HasFlag(DrawMode::Textured) && object->GetTexture() == nullptr)
		{
			continue;
		}

		std::vector<Math::Vertex> objectVertices = object->GetVertexList();
		std::vector<int> objectIndices = object->GetIndexList();

		for (Math::Vertex& objectVertex : objectVertices)
		{
			objectVertex.pos = objectVertex.pos * viewMatrix;
		}

		for (int index = 0; index < objectIndices.size(); index += 3)
		{
			Triangle t;

			t.v0 = objectVertices[objectIndices[index + 0]];
			t.v1 = objectVertices[objectIndices[index + 1]];
			t.v2 = objectVertices[objectIndices[index + 2]];

			drawableTriangles.push_back(t);

			/*
			//if (t.v0.pos.z > 0 || t.v1.pos.z > 0 || t.v2.pos.z > 0)
			//{
			//	continue;
			//}

			//Do triangle clipping here
			//Mapscale = 64
			//Map = 16x16
			//CameraScaling = 0.025
			//Map: 0.0f -> 25.6f (every grid element is 1.6f wide)

			Triangle tClipped0, tClipped1;

			//int triNumber = ClipTriangle(Vec4({ 1.0f, 0.0f, 0.0f }), Vec4({ -1.0f, 0.0f, 0.0f }), t, tClipped0, tClipped1);
			//int triNumber = ClipTriangle(Vec4({ -12.8f, 0.0f, 0.0f }), Vec4({ 1.0f, 0.0f, 0.0f }), t, tClipped0, tClipped1);
			//int triNumber = ClipTriangle(Vec4({ 0.0f, -12.8f, 0.0f }), Vec4({ 0.0f, 1.0f, 0.0f }), t, tClipped0, tClipped1);
			int triNumber = ClipTriangle(Vec4({ 0.0f, 0.0f, -12.8f }), Vec4({ 0.0f, 0.0f, 1.0f }), t, tClipped0, tClipped1);

			
			if (triNumber == 1)
			{
				drawableTriangles.push_back(tClipped0);
			}
			else if (triNumber == 2)
			{
				drawableTriangles.push_back(tClipped0);
				drawableTriangles.push_back(tClipped1);
			}
			*/

		}
	}

	//ACTUAL DRAWING
	g->BeginDraw();
	g->SetDrawMode(drawMode);
	g->SetTexture(texture);

	g->SetFillColor(backgroundColor);
	g->DrawFilledRectangle(0, 0, this->GetWidth(), this->GetHeight());
	g->SetFillColor(focusColor);

	float viewportWidth = this->GetWidth();
	float viewportHeight = this->GetHeight();

	std::vector<Plane> clippingPlanes;

	//ClippingPlanes X
	clippingPlanes.push_back(Plane(Vec4({ 0.0f, 0.0f, 0.0f }), Vec4({ 1.0f, 0.0f, 0.0f })));
	clippingPlanes.push_back(Plane(Vec4({ viewportWidth, 0.0f, 0.0f }), Vec4({ -1.0f, 0.0f, 0.0f })));
	
	//ClippingPlanes Y
	clippingPlanes.push_back(Plane(Vec4({ 0.0f, 0.0f, 0.0f }), Vec4({ 0.0f, 1.0f, 0.0f })));
	clippingPlanes.push_back(Plane(Vec4({ 0.0f, viewportHeight, 0.0f }), Vec4({ 0.0f, -1.0f, 0.0f })));
	
	//ClippingPlanes Z
	clippingPlanes.push_back(Plane(Vec4({ 0.0f, 0.0f, -300.0f }), Vec4({ 0.0f, 0.0f, 1.0f })));
	//clippingPlanes.push_back(Plane(Vec4({ 0.0f, 0.0f, 30.0f }), Vec4({ 0.0f, 0.0f, -1.0f })));
	

	for (int i = 0; i < drawableTriangles.size(); i++)
	{
		Triangle& t = drawableTriangles[i];

		t.DoProject(projMatrix, screenWidth, screenHeight);
	}

	//CLIPPING
	//std::vector<Triangle> clippedTriangles;

	//Triangle& t = drawableTriangles[i];
	//clippedTriangles.push_back(t);

	//for (int i = 0; i < drawableTriangles.size(); i++)
	//{

	//	for (int j = 0; j < clippingPlanes.size(); j++)
	//	{
	//		Triangle tClipped0, tClipped1;

	//		int triNumber = ClipTriangle(clippingPlanes[j].planePoint, clippingPlanes[j].planeNormal, t, tClipped0, tClipped1);

	//		if (triNumber == 1)
	//		{
	//			clippedTriangles.push_back(tClipped0);
	//		}
	//		else if (triNumber == 2)
	//		{
	//			clippedTriangles.push_back(tClipped0);
	//			clippedTriangles.push_back(tClipped1);
	//		}
	//	}
	//}

	//triangleCount = drawableTriangles.size();
	
	
	std::vector<Triangle> clippedTriangles;
	Triangle tClipped0, tClipped1;

	for (Triangle& drawableTriangle : drawableTriangles)
	{
		//Every triangle will be clipped against multiple planes
		std::list<Triangle> newClippedTriangles;
		newClippedTriangles.push_back(drawableTriangle);
		int newClippedTrianglesCount = 1;

		for (Plane plane : clippingPlanes)
		{
			while (newClippedTrianglesCount > 0)
			{
				Triangle testTriangle = newClippedTriangles.front();
				newClippedTriangles.pop_front();
				newClippedTrianglesCount--;

				int trianglesToAdd = ClipTriangle(plane.planePoint, plane.planeNormal, testTriangle, tClipped0, tClipped1);

				if (trianglesToAdd == 1)
				{
					newClippedTriangles.push_back(tClipped0);
				}
				else if (trianglesToAdd == 2)
				{
					newClippedTriangles.push_back(tClipped0);
					newClippedTriangles.push_back(tClipped1);
				}
			}

			newClippedTrianglesCount = newClippedTriangles.size();
		}

		//Copy clipped Triangles
		for (Triangle& clippedTriangle : newClippedTriangles)
		{
			clippedTriangles.push_back(clippedTriangle);
		}
	}

	//DRAWING
	//for (Triangle& t : drawableTriangles)
	for (Triangle& t : clippedTriangles)
	{
		if (t.v0.pos.z > -10 || t.v1.pos.z > -10 || t.v2.pos.z > -10)
		{
			//continue;
		}

		g->DrawTriangle(t.v0, t.v1, t.v2);
	}

	//triangleCount = clippedTriangles.size();

	// DRAW SELECTED OBJECT
	//if (selectedObject != nullptr)
	//{
	//	g->SetDrawMode(DrawMode::Filled);
	//	g->SetPenColor(focusColor);
	//	g->SetFillColor(focusColor);

 //		std::vector<Math::Vertex> objectVertices = selectedObject->GetVertexList();
	//	std::vector<int> objectIndices = selectedObject->GetIndexList();

	//	for (Math::Vertex& objectVertex : objectVertices)
	//	{
	//		objectVertex.pos = objectVertex.pos * projMatrix;//cameraMatrix;

	//		//Do Project

	//		//objectVertex.pos.z += 3.0f;

	//		if (objectVertex.pos.w != 0)
	//		{
	//			objectVertex.pos.x /= objectVertex.pos.w;
	//			objectVertex.pos.y /= objectVertex.pos.w;
	//		}

	//		objectVertex.pos.x = (objectVertex.pos.x + 1.0f) * screenWidth * 0.5f;
	//		objectVertex.pos.y = (objectVertex.pos.y + 1.0f) * screenHeight * 0.5f;
	//	}

	//	for (int index = 0; index < objectVertices.size(); index += 3)
	//	{
	//		Vertex v0 = objectVertices[objectIndices[index + 0]];
	//		Vertex v1 = objectVertices[objectIndices[index + 1]];
	//		Vertex v2 = objectVertices[objectIndices[index + 2]];

	//		if (v0.pos.z > 0 || v1.pos.z > 0 || v2.pos.z > 0)
	//		{
	//			continue;
	//		}

	//		g->DrawTriangle(v0, v1, v2);
	//	}
	//}

	////It's done here since the SelectionBuffer data only exists while we are drawing
	//if (isSelectionChanged)
	//{
	//	int objectId = RendererFront::GetSelectionBufferValue(mouseX, mouseY);

	//	selectedObject = renderedLevel->GetObjectFromId(objectId);

	//	isSelectionChanged = false;
	//}







	////===================================




	////g->SetTexture();

	////Vertices and Indices are interogated and decided if they would go into
	////the global vertex object list to be rendered

	//std::vector<Math::Vertex> drawableVerticesList; //This can be stored (this and the indexlist essentially does not change if we didn't alter the level!)
	//std::vector<int> drawableIndicesList;
	//int objectVerticesCount = 0;

	//for (int i = 0; i < renderedLevel->objectList.size(); i++)
	//{
	//	//Get Object Vertices
	//	std::vector<Math::Vertex> objectVertices = renderedLevel->objectList[i]->GetVertexList();

	//	for (Math::Vertex objectVertex : objectVertices)
	//	{
	//		drawableVerticesList.push_back(objectVertex);
	//	}

	//	//Get Object Indices
	//	
	//	std::vector<int> objectIndices = renderedLevel->objectList[i]->GetIndexList();

	//	for (int objectIndex : objectIndices)
	//	{
	//		objectIndex += objectVerticesCount;
	//		drawableIndicesList.push_back(objectIndex);
	//	}

	//	objectVerticesCount += objectVertices.size();
	//}

	//

	////for (Math::Vertex& drawableVertex : drawableVerticesList)
	////{
	////	drawableVertex.pos = drawableVertex.pos * cameraMatrix;
	////	//drawableVertex.pos *= cameraMatrix;
	////	//drawableVertex.pos = drawableVertex.pos + Vec4(400, 300, 0, 0);
	////}

	//g->SetPenColor(AssetManager::CreateColor(255, 255, 0, 0));

	//for (Math::Vertex& drawableVertex : drawableVerticesList)
	//{
	//	g->DrawLine(drawableVertex.pos.x - 1, drawableVertex.pos.y - 1, drawableVertex.pos.x + 2, drawableVertex.pos.y + 2);
	//	g->DrawLine(drawableVertex.pos.x + 1, drawableVertex.pos.y - 1, drawableVertex.pos.x - 2, drawableVertex.pos.y + 2);
	//}

	//g->SetPenColor(AssetManager::CreateColor(255, 255, 128, 0));

	//for (int index = 0; index < drawableIndicesList.size(); index += 3)
	//{
	//	//Test triangle
	//	//Vec4 v0 = Vec4(100, 100, 0);
	//	//Vec4 v1 = Vec4(150, 150, 0);
	//	//Vec4 v2 = Vec4(120, 200, 0);
	//	//Vec4 v0 = Vec4(150, 100, 0);
	//	//Vec4 v1 = Vec4(100, 150, 0);
	//	//Vec4 v2 = Vec4(120, 200, 0);
	//	//Vec4 v0 = Vec4(150, 100, 0);
	//	//Vec4 v2 = Vec4(100, 150, 0);
	//	//Vec4 v1 = Vec4(120, 200, 0);
	//	//Vec4 v0 = Vec4(150, 100, 0);
	//	//Vec4 v1 = Vec4(150, 150, 0);
	//	//Vec4 v2 = Vec4(120, 200, 0);

	//	//Draw triangles using the Index Buffer
	//	Vertex v0 = drawableVerticesList[drawableIndicesList[index + 0]];
	//	Vertex v1 = drawableVerticesList[drawableIndicesList[index + 1]];
	//	Vertex v2 = drawableVerticesList[drawableIndicesList[index + 2]];

	//	Color* fillColor = new Color(v0.color.x * 255, v0.color.y * 255, v0.color.z * 255, v0.color.w * 255);
	//	fillColor->SetIndex(fillColor->GetRed() / 32 * 32 + fillColor->GetGreen() / 32 * 4 + fillColor->GetBlue() / 64);
	//	if (fillColor->GetIndex() == 0) fillColor->SetIndex(132);
	//	g->SetFillColor(fillColor);

	//	//Backface-culling

	//	Vec4 normalVec = CrossVec4((v2.pos - v0.pos), (v1.pos - v0.pos));

	//	//if (normalVec.z <= 0)
	//	{
	//		g->DrawTriangle(v0, v1, v2);
	//	}		

	//	//g->DrawTriangle(v0, v1, v2);

	//	delete fillColor;
	//}

	//triangleCount = drawableIndicesList.size() / 3;

	//Draw Player

	Vec4 playerPos = renderedLevel->player->GetPosition();
	playerPos = playerPos * viewMatrix;

	g->SetPenColor(playerColor);
	g->DrawRectangle(playerPos.x - 5, playerPos.y - 5, playerPos.x + 5, playerPos.y + 5);

	//Get objectId under mouse

	g->EndDraw();
}

void Viewport::DisplayPerformanceStats(GraphicsContext* g)
{

	std::string triangleCountText = "Triangles: " + std::to_string(triangleCount);

	int fpsCount = GameEngine::GetFPS();
	std::string fpsCountText = "FPS: " + std::to_string(fpsCount);

	std::string objectText;
	if (selectedObject != nullptr)
	{
		objectText = "SelectedObjectID: " + std::to_string(selectedObject->GetObjectId());
	}
	else
	{
		objectText = "SelectedObjectID: NULL";
	}	

	int boundsX0 = 0;
	int boundsY0 = this->GetHeight() - 45;
	int boundsX1 = 450;
	int boundsY1 = this->GetHeight() - 20;

	g->SetFillColor(statsBackgroundColor);
	g->DrawFilledRectangle(boundsX0, boundsY0, boundsX1, boundsY1);

	g->SetPenColor(statsForegroundColor);
	g->DrawText(triangleCountText, AssetManager::GetDefaultFont(), boundsX0 + 10, boundsY0);
	g->DrawText(fpsCountText, AssetManager::GetDefaultFont(), boundsX0 + 150, boundsY0);
	g->DrawText(objectText, AssetManager::GetDefaultFont(), boundsX0 + 250, boundsY0);
}

void Viewport::DisplayPlayerStats(GraphicsContext* g)
{
	std::string healthText = "Health: " + std::to_string(renderedLevel->player->GetHealth());
	std::string positionText = "PositionY: " + std::to_string(renderedLevel->player->GetPosition().y);

	int boundsX0 = 0;
	int boundsY0 = this->GetHeight() - 70;
	int boundsX1 = 450;
	int boundsY1 = this->GetHeight() - 45;

	g->SetFillColor(statsBackgroundColor);
	g->DrawFilledRectangle(boundsX0, boundsY0, boundsX1, boundsY1);

	g->SetPenColor(statsForegroundColor);
	g->DrawText(healthText, AssetManager::GetDefaultFont(), boundsX0 + 10, boundsY0);
	g->DrawText(positionText, AssetManager::GetDefaultFont(), boundsX0 + 150, boundsY0);
}

void Viewport::Draw(GraphicsContext* g)
{
	if (camera == nullptr || renderedLevel == nullptr)
	{
		DisplayDrawError(g);
		return;
	}

	DisplayLevel(g);
	DisplayPerformanceStats(g);
	//DisplayPlayerStats(g);

	if (GetIsFocused())
	{
		g->BeginDraw();
		g->SetPenColor(focusColor);
		g->DrawRectangle(0, 0, this->GetWidth() - 1, this->GetHeight() - 1);
		g->DrawRectangle(1, 1, this->GetWidth() - 2, this->GetHeight() - 2);
		g->EndDraw();
	}
}

void Viewport::ProcessMessage(Message* msg)
{
	if (msg->type == MSG_KEYDOWN)
	{
		OnKeyDown(msg);
	}
}

void Viewport::PerformHitTest(int x, int y)
{
}

void Viewport::OnKeyDown(Message* msg)
{
	if (!this->GetIsFocused())
	{
		return;
	}

	HandleEditing(msg);
	HandleCameraOptions(msg);
}


void Viewport::HandleEditing(Message* msg)
{
	if (selectedObject == nullptr)
	{
		return;
	}

	if (msg->sdlEvent->key.keysym.sym == SDLK_SPACE)
	{
		GridCellType newCellType = GridCellType::Floor;
		GridCell* gridCell = nullptr;

		gridCell = renderedLevel->GetGridCellFromObject(selectedObject);

		if (gridCell == nullptr)
		{
			return;
		}

		if (gridCell->cellType == GridCellType::Empty)
		{
			newCellType = GridCellType::Floor;
		}
		else if (gridCell->cellType == GridCellType::Floor)
		{
			newCellType = GridCellType::Block;
		}
		else if (gridCell->cellType == GridCellType::Block)
		{
			newCellType = GridCellType::Empty;
		}

		renderedLevel->ReplaceCell(gridCell, newCellType);

		selectedObject = gridCell->levelObject;
	}
	else if (msg->sdlEvent->key.keysym.sym == SDLK_0)
	{
		selectedObject->SetTexture(AssetManager::CreateTextureAtlas("TestTexture0.png"));
	}
	else if (msg->sdlEvent->key.keysym.sym == SDLK_1)
	{
		selectedObject->SetTexture(AssetManager::CreateTextureAtlas("TestTexture1.png"));
	}
	else if (msg->sdlEvent->key.keysym.sym == SDLK_2)
	{
		selectedObject->SetTexture(AssetManager::CreateTextureAtlas("TestTexture2.png"));
	}
	else if (msg->sdlEvent->key.keysym.sym == SDLK_3)
	{
		selectedObject->SetTexture(AssetManager::CreateTextureAtlas("TestTexture3.png"));
	}
	else if (msg->sdlEvent->key.keysym.sym == SDLK_4)
	{
		selectedObject->SetTexture(AssetManager::CreateTextureAtlas("TestTexture4.png"));
	}
	else if (msg->sdlEvent->key.keysym.sym == SDLK_5)
	{
		selectedObject->SetTexture(AssetManager::CreateTextureAtlas("TestTexture5.png"));
	}
	else if (msg->sdlEvent->key.keysym.sym == SDLK_6)
	{
		selectedObject->SetTexture(AssetManager::CreateTextureAtlas("TestTexture6.png"));
	}
	else if (msg->sdlEvent->key.keysym.sym == SDLK_7)
	{
		selectedObject->SetTexture(AssetManager::CreateTextureAtlas("TestTexture7.png"));
	}
	else if (msg->sdlEvent->key.keysym.sym == SDLK_8)
	{
		selectedObject->SetTexture(AssetManager::CreateTextureAtlas("TestTexture8.png"));
	}
	else if (msg->sdlEvent->key.keysym.sym == SDLK_9)
	{
		selectedObject->SetTexture(AssetManager::CreateTextureAtlas("TestTexture9.png"));
	}
}

void Viewport::HandleCameraOptions(Message* msg)
{
	if (msg->sdlEvent->key.keysym.sym == SDLK_RIGHT)
	{
		camera->angleY += Math::DegreeToRadian(1.0f);
	}
	else if (msg->sdlEvent->key.keysym.sym == SDLK_LEFT)
	{
		camera->angleY -= Math::DegreeToRadian(1.0f);
	}
	else if (msg->sdlEvent->key.keysym.sym == SDLK_UP)
	{
		camera->angleX += Math::DegreeToRadian(1.0f);
	}
	else if (msg->sdlEvent->key.keysym.sym == SDLK_DOWN)
	{
		camera->angleX -= Math::DegreeToRadian(1.0f);
	}
	else if (msg->sdlEvent->key.keysym.sym == SDLK_PAGEUP)
	{
		//camera->scaling *= 1.01;
		camera->scaling *= 1.03;
	}
	else if (msg->sdlEvent->key.keysym.sym == SDLK_PAGEDOWN)
	{
		//camera->scaling /= 1.01;
		camera->scaling /= 1.03;
	}
	else if (msg->sdlEvent->key.keysym.sym == SDLK_w)
	{
		camera->posY -= 0.1f;
	}
	else if (msg->sdlEvent->key.keysym.sym == SDLK_s)
	{
		camera->posY += 0.1f;
	}
	else if (msg->sdlEvent->key.keysym.sym == SDLK_a)
	{
		camera->posX -= 0.1f;
	}
	else if (msg->sdlEvent->key.keysym.sym == SDLK_d)
	{
		camera->posX += 0.1f;
	}
	else if (msg->sdlEvent->key.keysym.sym == SDLK_q)
	{
		camera->posZ -= 0.1f;
	}
	else if (msg->sdlEvent->key.keysym.sym == SDLK_e)
	{
		camera->posZ += 0.1f;
	}
}

void Viewport::OnMouseClick(Message* msg)
{
	//Update and ProcessMessage calls are performed after we cleared the Buffers
	//They will be empty, so grabbing anything from them before drawing won't result anything

	mouseX = msg->sdlEvent->button.x;
	mouseY = msg->sdlEvent->button.y;

	isSelectionChanged = true;

	ControlNode::OnMouseClick(msg);
}

