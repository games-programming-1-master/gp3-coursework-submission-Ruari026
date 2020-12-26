#pragma once
#include "Component.h"
#include "Button.h"

class MainMenuManager : public Component
{
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
};