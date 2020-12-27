#include "pch.h"
#include "OptionsMenuManager.h"
#include "Entity.h"
#include "Input.h"

OptionsMenuManager::OptionsMenuManager()
{
}

OptionsMenuManager::~OptionsMenuManager()
{
}


/*
========================================================================================================================================================================================================
Inherited Component Methods
========================================================================================================================================================================================================
*/
void OptionsMenuManager::OnStart()
{
}

void OptionsMenuManager::OnUpdate(float deltaTime)
{
	//glm::ivec2 mousePos = Input::GetInstance()->GetMousePos();
	//SDL_GetMouseState(&mousePos.x, &mousePos.y);
	//Log::Debug(std::to_string(mousePos.x) + ", " + std::to_string(mousePos.y), "", 0);
}

void OptionsMenuManager::OnRender()
{

}


/*
========================================================================================================================================================================================================
Scene Button Methods
========================================================================================================================================================================================================
*/
void OptionsMenuManager::ReturnToMainMenu(bool saveChanges)
{
	// User may not want to save the changes they made to the options
	// Persistant data holds the saved options values
	if (saveChanges)
	{

	}

	// Hiding Options Menu
	optionsMenuParent->SetEnabled(false);

	// Showing Main Menu
	mainMenuParent->SetEnabled(true);
}