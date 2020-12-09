#pragma once
#include "Component.h"
class LevelManager : Component
{
public:
	LevelManager();

	// Inherited component methods
	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	// Level Generation Handling
	void GenerateLevel();
};