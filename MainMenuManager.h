#pragma once
#include "Component.h"

class MainMenuManager : public Component
{
private:
	Entity* mainMenuParent = nullptr;
	Entity* optionsMenuParent = nullptr;

public:
	MainMenuManager();
	virtual ~MainMenuManager() override;

	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender();

	//Methods to be called from scene buttons
	void StartGame();
	void OpenOptions();
	void QuitGame();

	// Assigning Scene Specific Objects
	void SetMenuParents(Entity* mainMenu, Entity* optionsMenu) { mainMenuParent = mainMenu; optionsMenuParent = optionsMenu; }
};