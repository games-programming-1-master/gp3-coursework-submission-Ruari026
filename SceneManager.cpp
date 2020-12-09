#include "SceneManager.h"
#include "MainMenuScene.h"
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
Loading Game Scenes
====================================================================================================
*/
void SceneManager::Init(std::string startScene)
{
	// Loading Main Menu Scene
	gameScenes.insert(std::pair<std::string, Scene*>("Main Menu", new MainMenuScene()));
	// Loading Gameplay Scene
	gameScenes.insert(std::pair<std::string, Scene*>("Gameplay", new GameplayScene()));
	// Loading Game Over Scene
	gameScenes.insert(std::pair<std::string, Scene*>("Game Over", new GameOverScene()));

	// Setting start scene
	this->currentScene = gameScenes[startScene];
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
void SceneManager::ChangeScene(std::string newScene)
{
	this->currentScene = gameScenes[newScene];
}