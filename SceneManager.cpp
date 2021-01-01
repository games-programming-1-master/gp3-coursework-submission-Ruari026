#include "SceneManager.h"
#include "MainMenuScene.h"
#include "TutorialScene.h"
#include "GameplayScene.h"
#include "GameOverScene.h"

SceneManager* SceneManager::m_instance = nullptr;

/*
====================================================================================================
Singleton Design Pattern
====================================================================================================
*/
SceneManager::SceneManager()
{

}

SceneManager* SceneManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new SceneManager();
	}
	return m_instance;
}


/*
====================================================================================================
Running Current Game Scene
====================================================================================================
*/
Scene* SceneManager::GetCurrentScene()
{
	return this->currentScene;
}


/*
====================================================================================================
Changing Current Game Scene
====================================================================================================
*/
void SceneManager::SetStartScene(GameScenes startScene)
{
	// Saves the type of the scene
	newSceneType = startScene;

	// Creates a new scene of the requested type
	switch (startScene)
	{
		case (GameScenes::GAMESCENE_MAINMENU):
		{
			currentScene = new MainMenuScene();
		}
		break;

		case (GameScenes::GAMESCENE_TUTORIAL):
		{
			currentScene = new TutorialScene();
		}
		break;

		case (GameScenes::GAMESCENE_GAMEPLAY):
		{
			currentScene = new GameplayScene();
		}
		break;
	}

	// Ensures the new scene starts all of it's entity's
	currentScene->Start();
}

void SceneManager::CheckForSceneChange()
{
	if (changeScene)
	{
		// Ensures the old scene is destroyed properly
		delete currentScene;

		// Creates a new scene of the requested type
		if (changeScene)
		{
			switch (newSceneType)
			{
			case (GameScenes::GAMESCENE_MAINMENU):
			{
				currentScene = new MainMenuScene();
			}
			break;

			case (GameScenes::GAMESCENE_TUTORIAL):
			{
				currentScene = new TutorialScene();
			}
			break;

			case (GameScenes::GAMESCENE_GAMEPLAY):
			{
				currentScene = new GameplayScene();
			}
			break;
			}
		}

		// Ensures the new scene starts all of it's entity's
		currentScene->Start();

		// Prevents operation from happening again until requested
		changeScene = false;
	}
}

void SceneManager::QueueSceneChange(GameScenes newScene)
{
	changeScene = true;
	newSceneType = newScene;
}