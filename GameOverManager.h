#pragma once
#include "Component.h"
#include "TransitionRenderer.h"
#include "TextRenderer.h"
#include "Button.h"

enum class GameOverState
{
	STATE_TRANSITIONIN,
	STATE_GAMEOVERNORMAL,
	STATE_TRANSITIONOUT,
	STATE_CHANGESCENE
};

class GameOverManager : public Component
{
private:
	GameOverState currentState = GameOverState::STATE_TRANSITIONIN;

	float stateTimer = 0;
	float transitionTime = 15.0f;

	bool isReplayingGame;

	// Handling UI Elements
	TextRenderer* gameStatsText;
	TransitionRenderer* theTransitionController;
	std::vector<Button*> sceneButtons;

public:
	GameOverManager();
	virtual ~GameOverManager() override;

	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender();

	//Methods to be called from scene buttons
	void ReplayGame();
	void MoveToMenu();
	
	// Assigning Scene Specific Objects
	void SetTransitionController(TransitionRenderer* sceneController) { theTransitionController = sceneController; }
	void SetGameStatsText(TextRenderer* text) { gameStatsText = text; }
	void SetSceneButtons(std::vector<Button*> buttons) { sceneButtons = buttons; }

	// Controlling Scene State
	void ChangeSceneState(GameOverState newState);
};