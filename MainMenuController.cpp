#include "pch.h"
#include "MainMenuController.h"
#include "Entity.h"
#include "Input.h"

MainMenuController::MainMenuController()
{
}

MainMenuController::~MainMenuController()
{
}


/*
========================================================================================================================================================================================================
Inherited Component Methods
========================================================================================================================================================================================================
*/
void MainMenuController::OnStart()
{
}

void MainMenuController::OnUpdate(float deltaTime)
{
	glm::ivec2 mousePos = Input::GetInstance()->GetMousePos();
	SDL_GetMouseState(&mousePos.x, &mousePos.y);
	Log::Debug(std::to_string(mousePos.x) + ", " + std::to_string(mousePos.y), "", 0);
}

void MainMenuController::OnRender()
{

}