#pragma once
#include "Component.h"
#include "TextRenderer.h"

class OptionsMenuManager : public Component
{
private:
	Entity* mainMenuParent = nullptr;
	Entity* optionsMenuParent = nullptr;

	// Handling temporary storage of settings values
	unsigned int volume;
	unsigned int sensitivity;

	// UI Elements
	std::vector<TextRenderer*> volumeValueUI;
	std::vector<TextRenderer*> sensitivityValueUI;

public:
	OptionsMenuManager();
	virtual ~OptionsMenuManager() override;

	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender();

	//Methods to be called from scene buttons
	void GetSavedSettings();
	void ChangeVolume(bool isIncreasing);
	void ChangeSensitivity(bool isIncreasing);
	void ReturnToMainMenu(bool saveChanges);

	// Assigning Scene Specific Objects
	void SetMenuParents(Entity* mainMenu, Entity* optionsMenu) { mainMenuParent = mainMenu; optionsMenuParent = optionsMenu; }
	void SetVolumeUI(std::vector<TextRenderer*> sceneVolumeUI) { volumeValueUI = sceneVolumeUI; }
	void SetSensitivityUI(std::vector<TextRenderer*> sceneSensitivityUI) { sensitivityValueUI = sceneSensitivityUI; }
};