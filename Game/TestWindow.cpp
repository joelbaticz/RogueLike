#include "TestWindow.h"
#include "Test1.h"

Test1* test1;

TestWindow::TestWindow()
{
	LogEngine::Log(LOG_DEBUG, "TestWindow", "Constructor called.");

	this->SetName("TestWindow");
	this->SetTitle("TestWindow");
	this->SetIsVisible(true);
	this->SetX(450);
	this->SetY(250);
	this->SetSize(new Size(320, 320));

	test1 = new Test1();
	this->AddChild(test1);
}

TestWindow::~TestWindow()
{
	LogEngine::Log(LOG_DEBUG, "TestWindow", "Destructor called.");
}

void TestWindow::Update()
{

}

void TestWindow::Draw(GraphicsContext* g)
{

}