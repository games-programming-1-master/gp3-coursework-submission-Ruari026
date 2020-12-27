#include "pch.h"
#include "TutorialManager.h"
#include "SceneManager.h"

TutorialManager::TutorialManager()
{
}

TutorialManager::~TutorialManager()
{
}


/*
========================================================================================================================================================================================================
Inherited Component Methods
========================================================================================================================================================================================================
*/
void TutorialManager::OnStart()
{
	// Picks what variation of the tutorial scene to show based on the players last level

	// Gets the games persistant data
	// If current level is 0 then the player has started a new game - show the controls first

	// Otherwise show other story scenes (triggered after level 5 and 10)
}

void TutorialManager::OnUpdate(float deltaTime)
{
	// Background Ghost Animation
}

void TutorialManager::OnRender()
{

}


/*
========================================================================================================================================================================================================
Scene Button Methods
========================================================================================================================================================================================================
*/
void TutorialManager::OpenControls()
{
	// Ensures all story elements are hidden
	story1Parent->SetEnabled(false);

	// Showing Controls elements
	controlsParent->SetEnabled(true);
}

void TutorialManager::MoveToGame()
{
	SceneManager::GetInstance()->ChangeScene("Gameplay");
}