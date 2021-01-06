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

	// Handling main timer
	float timeRemaining;

	// Handling Level Score
	int ghostsRemaining;

	// UI Handling
	// Parents
	Entity* gameplayUIParent = nullptr;
	Entity* pauseUIParent = nullptr;
	// Texts
	std::vector<TextRenderer*> timerTextRenderers;
	std::vector<TextRenderer*> mimicsTextRenderers;

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
	void SetSceneTimerUI(std::vector<TextRenderer*> timerRenderers) { timerTextRenderers = timerRenderers; }
	void SetSceneGhostsUI(std::vector<TextRenderer*> ghostsRenderers) { mimicsTextRenderers = ghostsRenderers; }
	// Pause Menu UI Elements
	void SetPauseScreenButtons(std::vector<Button*> pauseButtons) { pauseUIButtons = pauseButtons; }
	void SetTransitionController(TransitionRenderer* sceneController) { theTransitionController = sceneController; }

	// Controlling Scene State
	void ChangeSceneState(GameplayState newState);
	GameplayState GetCurrentState() { return currentState; }

	// Handling Game/ Level Score
	void OnMimicKilled();
	void SetLevelMimics(int numberOfGhosts);
};