#pragma once
#include "Component.h"

class OptionsMenuManager : public Component
{
private:
	Entity* mainMenuParent = nullptr;
	Entity* optionsMenuParent = nullptr;

public:
	OptionsMenuManager();
	virtual ~OptionsMenuManager() override;

	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender();

	//Methods to be called from scene buttons
	void ReturnToMainMenu(bool saveChanges);

	// Assigning Scene Specific Objects
	void SetMenuParents(Entity* mainMenu, Entity* optionsMenu) { mainMenuParent = mainMenu; optionsMenuParent = optionsMenu; }
};