#pragma once
#include "Component.h"
#include "Button.h"

class MainMenuController : public Component
{
public:
	MainMenuController();
	virtual ~MainMenuController() override;

	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender();
};