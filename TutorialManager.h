#pragma once
#include "Component.h"
#include "TransitionRenderer.h"

enum class TutorialState
{
	STATE_TRANSITIONIN,
	STATE_TUTORIALNORMAL,
	STATE_TRANSITIONOUT,
	STATE_STARTGAMEPLAY
};

class TutorialManager : public Component
{
private:
	TutorialState currentState = TutorialState::STATE_TRANSITIONIN;

	float stateTimer = 0;
	float transitionTime = 15.0f;

	Entity* controlsParent = nullptr;
	Entity* story1Parent = nullptr;
	Entity* story2Parent = nullptr;
	Entity* story3Parent = nullptr;

	TransitionRenderer* theTransitionController;

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
	void SetSceneParents(Entity* controls, Entity* story1, Entity* story2, Entity* story3) { controlsParent = controls; story1Parent = story1;  story2Parent = story2; story3Parent = story3;}
	void SetTransitionController(TransitionRenderer* sceneController) { theTransitionController = sceneController; }

	// Controlling Scene State
	void ChangeSceneState(TutorialState newState);
};