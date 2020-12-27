#pragma once
#include "Component.h"
class TutorialManager : public Component
{
private:
	Entity* controlsParent = nullptr;
	Entity* story1Parent = nullptr;

public:
	TutorialManager();
	virtual ~TutorialManager() override;

	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender();

	//Methods to be called from scene buttons
	void OpenControls();
	void MoveToGame();

	// Assigning Scene Specific Objects
	void SetSceneParents(Entity* controls, Entity* story) { controlsParent = controls; story1Parent = story; }
};