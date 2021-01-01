#pragma once
#include "Component.h"
#include "TransitionRenderer.h"
#include "Button.h"

enum class MainMenuState
{
	STATE_MAINMENU,
	STATE_OPTIONSMOVE,
	STATE_OPTIONSMENU,
	STATE_MAINMENUMOVE,
	STATE_TUTORIALTRANSITION,
	STATE_TUTORIALSTART,
	STATE_QUITTRANSITION,
	STATE_QUITGAME
};

class MainMenuManager : public Component
{
private:
	MainMenuState currentState = MainMenuState::STATE_MAINMENU;
	
	float stateTimer = 0;
	float lerpTime = 22.5f;
	float transitionTime = 15.0f;

	Entity* sceneCamera = nullptr;
	Entity* mainMenuParent = nullptr;
	Entity* optionsMenuParent = nullptr;

	glm::vec3 mainMenuCameraPos = glm::vec3(-0.5f, 1.5f, -3.0f);
	glm::quat mainMenuCameraRot = Utility::GetRotationQuaternion((M_PI * -1.167f), glm::vec3(0, 1, 0));

	glm::vec3 optionsMenuCameraPos = glm::vec3(4.5f, 1.5f, 0.0f);
	glm::quat optionsMenuCameraRot = Utility::GetRotationQuaternion((M_PI * -0.5f), glm::vec3(0, 1, 0));

	std::vector<Button*> mainMenuButtons;
	TransitionRenderer* theTransitionController;

public:
	MainMenuManager();
	virtual ~MainMenuManager() override;

	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender();

	//Methods to be called from scene buttons
	void StartGame();
	void OpenOptions();
	void QuitGame();

	// Assigning Scene Specific Objects
	void SetSceneCamera(Entity* camera) { sceneCamera = camera; }
	void SetMenuParents(Entity* mainMenu, Entity* optionsMenu) { mainMenuParent = mainMenu; optionsMenuParent = optionsMenu; }
	void SetMenuButtons(std::vector<Button*> sceneButtons) { mainMenuButtons = sceneButtons; }
	void SetTransitionController(TransitionRenderer* sceneController) { theTransitionController = sceneController; }

	// Controlling Scene State
	void ChangeSceneState(MainMenuState newState);
};