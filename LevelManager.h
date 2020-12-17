#pragma once
#include "Component.h"
class LevelManager : Component
{
private:

public:
	LevelManager();
	virtual ~LevelManager() override;

	// Inherited component methods
	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;
};