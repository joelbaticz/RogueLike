#include "SettingsWindow.h"
#include "MessageBox.h"
#include <intrin.h>
#include "RendererFront.h"
#include "Configuration.h"
#include "GameEngine.h"
//#include <windows.h>

//#include <SDL.h>

SettingsWindow::SettingsWindow()
{
	int windowWidth = 500;
	int windowHeight = 350;
	int windowX = (RendererFront::GetWindowWidth() - windowWidth) / 2;
	int windowY = (RendererFront::GetWindowHeight() - windowHeight) / 2;

	int controlWidth = 250;
	int controlHeight = 20;
	int controlXColumn1 = 20;
	int controlXColumn2 = windowWidth - controlWidth - 20;
	int controlY = 40;
	int controlYStep = 25;

	this->SetName("SettingsWindow");
	this->SetTitle("Settings");
	this->SetX(windowX);
	this->SetY(windowY);
	this->SetSize(new Size(windowWidth, windowHeight));
	this->GetContextMenuButton()->SetIsVisible(false);
	this->GetMinimizeButton()->SetIsVisible(false);
	this->GetMaximizeButton()->SetIsVisible(false);

	labelProcessorInfo = new Label(this, "labelProcessorInfo", "Processor:", controlXColumn1, controlY, controlWidth, controlHeight);
	labelProcessorInfoValue = new Label(this, "labelProcessorInfoValue", "", controlXColumn2, controlY, controlWidth, controlHeight);
	controlY += controlYStep;

	labelSystemMemoryInfo = new Label(this, "labelSystemMemoryInfo", "Total memory:", controlXColumn1, controlY, controlWidth, controlHeight);
	labelSystemMemoryInfoValue = new Label(this, "labelSystemMemoryInfoValue", "", controlXColumn2, controlY, controlWidth, controlHeight);
	controlY += controlYStep;

	labelRendererInfo = new Label(this, "labelRendererInfo", "Renderer:", controlXColumn1, controlY, controlWidth, controlHeight);
	labelRendererInfoValue = new Label(this, "labelRendererInfoValue", "", controlXColumn2, controlY, controlWidth, controlHeight);
	controlY += controlYStep;

	labelCurrentResolution = new Label(this, "labelCurrentResolution", "Current resolution:", controlXColumn1, controlY, controlWidth, controlHeight);
	labelCurrentResolutionValue = new Label(this, "labelCurrentResolutionValue", "", controlXColumn2, controlY, controlWidth, controlHeight);
	controlY += controlYStep;

	labelNewResolution = new Label(this, "labelNewResolution", "Resolution:", controlXColumn1, controlY, controlWidth, controlHeight);
	dropdownNewResolution = new Listbox(this, "dropdownNewResolution", controlXColumn2, controlY, controlWidth, 150);
	controlY += 155;

	buttonCancel = new Button(this, "buttonCancel", "Cancel", windowWidth - 90, windowHeight - 55, 80, 30);
	buttonRestart = new Button(this, "buttonRestart", "Restart", windowWidth - 180, windowHeight - 55, 80, 30);
	buttonRestart->SetIsEnabled(false);

	this->AddChild(labelProcessorInfo);
	this->AddChild(labelProcessorInfoValue);
	this->AddChild(labelSystemMemoryInfo);
	this->AddChild(labelSystemMemoryInfoValue);
	this->AddChild(labelRendererInfo);
	this->AddChild(labelRendererInfoValue);
	this->AddChild(labelCurrentResolution);
	this->AddChild(labelCurrentResolutionValue);
	this->AddChild(labelNewResolution);
	this->AddChild(dropdownNewResolution);

	this->AddChild(buttonCancel);
	this->AddChild(buttonRestart);

	InitializeSettings();
}

SettingsWindow::~SettingsWindow() = default;

std::string GetProcessorInfoString()
{
	int CPUInfo[4] = { -1 };
	char CPUBrandString[0x40];
	__cpuid(CPUInfo, 0x80000000);
	unsigned int nExIds = CPUInfo[0];

	memset(CPUBrandString, 0, sizeof(CPUBrandString));

	// Get the information associated with each extended ID.
	for (int i = 0x80000000; i <= nExIds; ++i)
	{
		__cpuid(CPUInfo, i);
		// Interpret CPU brand string.
		if (i == 0x80000002)
			memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
		else if (i == 0x80000003)
			memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
		else if (i == 0x80000004)
			memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
	}

	return CPUBrandString;
}

std::string GetSystemMemoryInfoString()
{
	std::string systemMemoryInfoString;

	//MEMORYSTATUSEX status;
	//status.dwLength = sizeof(status);
	//GlobalMemoryStatusEx(&status);

	//uint32_t totalPhysicalMemoryInMegaBytes = status.ullTotalPhys / 1024 / 1024;

	//systemMemoryInfoString = std::to_string(totalPhysicalMemoryInMegaBytes) + "MB";

	systemMemoryInfoString = std::to_string(SDL_GetSystemRAM()) + "MB";

	return systemMemoryInfoString;
}

std::string GetRendererInfoString()
{
	std::string rendererInfoString;

	SDL_RendererInfo rendererInfo = SDL_RendererInfo();

	SDL_GetRendererInfo(RendererFront::GetRenderer(), &rendererInfo);

	rendererInfoString = "";

	if ((rendererInfo.flags & SDL_RENDERER_SOFTWARE) == SDL_RENDERER_SOFTWARE)
	{
		rendererInfoString += "Software Rasterizer";
	}
	if ((rendererInfo.flags & SDL_RENDERER_ACCELERATED) == SDL_RENDERER_ACCELERATED)
	{
		rendererInfoString += "Hardware Accelerated";
	}

	rendererInfoString += " (";
	rendererInfoString += rendererInfo.name;
	rendererInfoString += +")";

	return rendererInfoString;
}

std::string GetCurrentResolutionString()
{
	return std::to_string(RendererFront::GetWindowWidth()) + "x" + std::to_string(RendererFront::GetWindowHeight());
}

std::vector<std::string>* SettingsWindow::GetAvailableResolutionsList()
{
	int displayIndex = 0;
	SDL_DisplayMode displayModeInfo;
	std::string displayModeText;

	displayModes.clear();
	std::vector<std::string>* displayModesStringList = new std::vector<std::string>();

	int displayModeCount = SDL_GetNumDisplayModes(displayIndex);

	for(int i = 0; i < displayModeCount; i++)
	{
		if (SDL_GetDisplayMode(displayIndex, i, &displayModeInfo) == 0)
		{
			std::string displayWidthString = std::to_string(displayModeInfo.w);
			std::string displayHeightString = std::to_string(displayModeInfo.h);
			std::string displayRefreshRateString = std::to_string(displayModeInfo.refresh_rate);

			displayModeText = displayWidthString + "x" + displayHeightString + "@" + displayRefreshRateString;

			if (displayModeInfo.refresh_rate == 60)
			{
				DisplayMode displayMode;
				displayMode.width = displayModeInfo.w;
				displayMode.height = displayModeInfo.h;
				displayMode.refreshRate = displayModeInfo.refresh_rate;
				displayMode.displayText = displayModeText;

				displayModes.push_back(displayMode);
				displayModesStringList->push_back(displayModeText);
			}			
		};
	}

	return displayModesStringList;
}

void SettingsWindow::InitializeSettings()
{
	// Processor info

	labelProcessorInfoValue->SetText(GetProcessorInfoString());

	// System memory info

	labelSystemMemoryInfoValue->SetText(GetSystemMemoryInfoString());

	// Renderer info

	labelRendererInfoValue->SetText(GetRendererInfoString());

	// Current Resolution

	labelCurrentResolutionValue->SetText(GetCurrentResolutionString());

	// New Resolution

	//dropdownNewResolution->SetCaption(GetCurrentResolutionString());
	dropdownNewResolution->SetList(GetAvailableResolutionsList());
	dropdownNewResolution->SetSelectedIndex(3);
}

void SettingsWindow::ProcessMessage(Message* msg)
{
	if (msg->type == MSG_BUTTON_CLICKED)
	{
		if (msg->sender == buttonCancel || msg->sender == this->GetCloseButton())
		{
			this->SetIsVisible(false);
		}

		if (msg->sender == buttonRestart)
		{
			Configuration::IsRestart = true;
			GameEngine::StopLoop();
		}
	}

	if (msg->type == MSG_LISTBOX_SELECTIONCHANGED)
	{
		if (msg->sender == dropdownNewResolution)
		{
			int selectedIndex = dropdownNewResolution->GetSelectedIndex();
			DisplayMode selectedDisplayMode = displayModes[selectedIndex];

			MessageBox::ShowMessage("Selection changed", "Chosen resolution: " + selectedDisplayMode.displayText, Ok);

			Configuration::WindowWidth = selectedDisplayMode.width;
			Configuration::WindowHeight = selectedDisplayMode.height;
			buttonRestart->SetIsEnabled(true);
		}
	}
}




