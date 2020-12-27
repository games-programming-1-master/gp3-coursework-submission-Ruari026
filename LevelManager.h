#pragma once
#include "Component.h"
class LevelManager : public Component
{
public:
	LevelManager();
	virtual ~LevelManager() override;

	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender();
};