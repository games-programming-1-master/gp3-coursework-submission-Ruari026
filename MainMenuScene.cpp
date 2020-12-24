#include "MainMenuScene.h"

MainMenuScene::MainMenuScene()
{
	// Every Scene Needs A Camera
	Entity* camera = new Entity("The Camera");
	m_entities.push_back(camera);
	this->SetCamera(new Camera(camera->GetTransform()));
	camera->GetTransform()->SetLocalPosition(glm::vec3(0, 0.5f, 0));

	// Spawning in the background environment

	// Handling UI Elements
	// Game Title
	Entity* gameTitle = new Entity("UI Title");
	m_entities.push_back(gameTitle);

	// Start Button

	// Options Button

	// Quit Button
}