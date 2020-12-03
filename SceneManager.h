#pragma once
#include "Scene.h"

class SceneManager
{
private:
	static SceneManager* m_instance;
	SceneManager();

	std::unordered_map<std::string, Scene*> gameScenes;
	Scene* currentScene = nullptr;

public:
	static SceneManager* GetInstance();

	void Init(std::string startScene);
	Scene* GetCurrentScene();
	void ChangeScene(std::string newScene);
};