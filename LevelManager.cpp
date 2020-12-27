#include "pch.h"
#include "LevelManager.h"
#include "Input.h"
#include "Application.h"

LevelManager::LevelManager()
{
}

LevelManager::~LevelManager()
{
}


/*
========================================================================================================================================================================================================
Inherited Component Methods
========================================================================================================================================================================================================
*/
void LevelManager::OnStart()
{
	// Ensures that the cursor is visible & unlocked
	Input::GetInstance()->LockAndHideCursor(SDL_TRUE);

	// Allows both the physics engine and component updates to run a normal speed
	Application::GetInstance()->SetUpdateTimeScale(1.0f);
	Application::GetInstance()->SetPhysicsTimeScale(1.0f);
}

void LevelManager::OnUpdate(float deltaTime)
{

}

void LevelManager::OnRender()
{

}