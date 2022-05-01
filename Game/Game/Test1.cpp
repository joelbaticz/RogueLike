#include "Test1.h"

#include <vector>
#include "AssetManager.h"

struct Point
{
	int x;
	int y;
	int dx;
	int dy;
};

Color* backgroundColor;
Color* lineColor;
Color* lineColor2;
Color* lineColor3;
std::vector<Point*> points;

Test1::Test1()
{
	this->SetName("Test1");
	this->SetIsVisible(true);
	this->SetLocation(new Location(0, 0));
	this->SetSize(new Size(250, 250));

	EventManager::Subscribe(this); // To receive Update messages

	backgroundColor = AssetManager::CreateColor(255, 5, 120, 240);
	lineColor = AssetManager::CreateColor(255, 64, 200, 255);
	lineColor2 = AssetManager::CreateColor(255, 16, 140, 240);
	lineColor3 = AssetManager::CreateColor(255, 8, 126, 240);
	
	points.push_back(new Point{ 50, 65, 1, 1 });
	points.push_back(new Point{ 100, 50, -1, 1 });
	points.push_back(new Point{ 100, 100, 1, 1 });
}

Test1::~Test1()
{

}

void Test1::Update()
{
	int boundsX0 = 0;
	int boundsY0 = 0;
	int boundsX1 = this->GetSize()->GetWidth();
	int boundsY1 = this->GetSize()->GetHeight();

	for (int i = 0; i < 3; i++)
	{
		points.at(i)->x += points.at(i)->dx;
		points.at(i)->y += points.at(i)->dy;

		if (points.at(i)->x < boundsX0 || points.at(i)->x > boundsX1)
		{
			points.at(i)->dx = -points.at(i)->dx;
		}
		if (points.at(i)->y < boundsY0 || points.at(i)->y > boundsY1)
		{
			points.at(i)->dy = -points.at(i)->dy;
		}
	}
}

void Test1::Draw(GraphicsContext* g)
{
	//this->Update();

	g->BeginDraw();

	g->SetFillColor(backgroundColor);
	g->DrawFilledRectangle(0, 0, this->GetSize()->GetWidth(), this->GetSize()->GetHeight());
	

	int fromX = points.at(0)->x;
	int fromY = points.at(0)->y;
	int toX = points.at(1)->x;
	int toY = points.at(1)->y;

	//g->SetPenColor(lineColor3);
	//g->DrawLine(fromX, fromY-2, toX, toY-2);
	//g->SetPenColor(lineColor2);
	//g->DrawLine(fromX, fromY - 1, toX, toY - 1);

	g->SetPenColor(lineColor);
	g->DrawLine(fromX, fromY, toX, toY);
	
	//g->SetPenColor(lineColor2);
	//g->DrawLine(fromX, fromY + 1, toX, toY + 1);
	//g->SetPenColor(lineColor3);
	//g->DrawLine(fromX, fromY + 2, toX, toY + 2);

	g->EndDraw();
}