#pragma once
#include "Scene.h"

enum class GameScenes
{
	GAMESCENE_MAINMENU,
	GAMESCENE_TUTORIAL,
	GAMESCENE_GAMEPLAY,
	GAMESCENE_GAMEOVER
};

class SceneManager
{
private:
	static SceneManager* m_instance;
	SceneManager();

	bool changeScene = false;
	GameScenes newSceneType;

	Scene* currentScene = nullptr;

public:
	static SceneManager* GetInstance();

	void SetStartScene(GameScenes startScene);

	Scene* GetCurrentScene();

	void CheckForSceneChange();
	void QueueSceneChange(GameScenes newScene);
};