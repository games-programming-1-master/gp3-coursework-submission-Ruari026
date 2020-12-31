#pragma once
#include "Component.h"
#include "TransitionRenderer.h"
#include "Button.h"

enum class GameplayState
{
	STATE_LEVELSTARTING,
	STATE_GAMEPLAY,
	STATE_GAMEPAUSED,
	STATE_TRANSITIONTOMAINMENU,
	STATE_MOVETOMAINMENU,
	STATE_TRANSITIONTONEXTLEVEL,
	STATE_MOVETONEXTLEVEL
};

class LevelManager : public Component
{
private:
	GameplayState currentState = GameplayState::STATE_LEVELSTARTING;

	float stateTimer = 0;
	float transitionTime = 15.0f;

	Entity* gameplayUIParent = nullptr;
	Entity* pauseUIParent = nullptr;

	std::vector<Button*> pauseUIButtons;
	TransitionRenderer* theTransitionController;

public:
	LevelManager();
	virtual ~LevelManager() override;

	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender();

	// Assigning Scene Specific Objects
	void SetSceneParents(Entity* gameplayUI, Entity* pauseUI) { gameplayUIParent = gameplayUI; pauseUIParent = pauseUI; }
	void SetPauseScreenButtons(std::vector<Button*> pauseButtons) { pauseUIButtons = pauseButtons; }
	void SetTransitionController(TransitionRenderer* sceneController) { theTransitionController = sceneController; }

	// Controlling Scene State
	void ChangeSceneState(GameplayState newState);
	GameplayState GetCurrentState() { return currentState; }
};