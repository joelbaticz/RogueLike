#pragma once
#include "ToolWindow.h"
#include "Label.h"
#include "Dropdown.h"
#include "Listbox.h"

struct DisplayMode
{
	int width;
	int height;
	int refreshRate;
	std::string displayText;
};

class SettingsWindow: public ToolWindow
{
private:
	Label* labelProcessorInfo;
	Label* labelProcessorInfoValue;
	Label* labelSystemMemoryInfo;
	Label* labelSystemMemoryInfoValue;
	Label* labelRendererInfo;
	Label* labelRendererInfoValue;
	Label* labelCurrentResolution;
	Label* labelCurrentResolutionValue;
	Label* labelNewResolution;
	Listbox* dropdownNewResolution;

	std::vector<DisplayMode> displayModes;
	
	Button* buttonCancel;
	Button* buttonRestart;

	void InitializeSettings();

	std::vector<std::string>* GetAvailableResolutionsList();
public:
	SettingsWindow();
	~SettingsWindow();

	void ProcessMessage(Message* msg) override;
};
