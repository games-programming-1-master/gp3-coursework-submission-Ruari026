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
	// Scene State Details
	GameplayState currentState = GameplayState::STATE_LEVELSTARTING;
	float stateTimer = 0;
	float transitionTime = 15.0f;

	// UI Parents
	Entity* gameplayUIParent = nullptr;
	Entity* pauseUIParent = nullptr;

	// Specific Gameplay UI elements
	TextRenderer* sceneUITimer;
	TextRenderer* ghostsUIAmount;

	// Specific pause menu UI elements
	std::vector<Button*> pauseUIButtons;
	TransitionRenderer* theTransitionController;

public:
	LevelManager();
	virtual ~LevelManager() override;

	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender();

	//Methods to be called from scene buttons
	void UnpauseGame();
	void ReturnToMenu();

	// Assigning Scene Specific Objects
	// Parents
	void SetSceneParents(Entity* gameplayUI, Entity* pauseUI) { gameplayUIParent = gameplayUI; pauseUIParent = pauseUI; }
	// Gameplay UI Elements
	void SetSceneTimerUI(TextRenderer* timerRenderer) { sceneUITimer = timerRenderer; }
	void SetSceneGhostsUI(TextRenderer* ghostsRenderer) { ghostsUIAmount = ghostsRenderer; }
	// Pause Menu UI Elements
	void SetPauseScreenButtons(std::vector<Button*> pauseButtons) { pauseUIButtons = pauseButtons; }
	void SetTransitionController(TransitionRenderer* sceneController) { theTransitionController = sceneController; }

	// Controlling Scene State
	void ChangeSceneState(GameplayState newState);
	GameplayState GetCurrentState() { return currentState; }
};