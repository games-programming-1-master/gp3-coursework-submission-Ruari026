#include "pch.h"
#include "MainMenuManager.h"
#include "Entity.h"
#include "Input.h"

MainMenuManager::MainMenuManager()
{
}

MainMenuManager::~MainMenuManager()
{
}


/*
========================================================================================================================================================================================================
Inherited Component Methods
========================================================================================================================================================================================================
*/
void MainMenuManager::OnStart()
{
}

void MainMenuManager::OnUpdate(float deltaTime)
{
	//glm::ivec2 mousePos = Input::GetInstance()->GetMousePos();
	//SDL_GetMouseState(&mousePos.x, &mousePos.y);
	//Log::Debug(std::to_string(mousePos.x) + ", " + std::to_string(mousePos.y), "", 0);
}

void MainMenuManager::OnRender()
{

}


/*
========================================================================================================================================================================================================
Scene Button Methods
========================================================================================================================================================================================================
*/
void MainMenuManager::StartGame()
{
	Log::Debug("Starting Game", "MainMenuController.cpp", 44);
}

void MainMenuManager::OpenOptions()
{
	Log::Debug("Opening Options", "MainMenuController.cpp", 49);
}

void MainMenuManager::QuitGame()
{
	Log::Debug("Quitting Game", "MainMenuController.cpp", 54);
}