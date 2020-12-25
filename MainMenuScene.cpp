#include "MainMenuScene.h"

// General Engine Includes
#include "Resources.h"
// Required Components
#include "TextRenderer.h"
#include "MainMenuController.h"

MainMenuScene::MainMenuScene()
{
	// Every Scene Needs A Camera
	Entity* camera = new Entity("The Camera");
	m_entities.push_back(camera);
	this->SetCamera(new Camera(camera->GetTransform()));
	camera->GetTransform()->SetLocalPosition(glm::vec3(0, 0.5f, 0));

	// Manager to control main menu behaviour
	Entity* menuController = new Entity("The Controller");
	m_entities.push_back(menuController);
	menuController->AddComponent<MainMenuController>();

	// Spawning in the background environment

	// Main Menu UI Elements
	// Game Title
	{
		Entity* gameTitle = new Entity("UI Title");
		gameTitle->GetTransform()->SetGlobalPosition(glm::vec3(125, 225, 1.0f));
		m_entities.push_back(gameTitle);

		gameTitle->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
				Resources::GetInstance()->GetShader("text"),
				100)
		);
		gameTitle->GetComponent<TextRenderer>()->SetTextToRender("The Mansion");
		gameTitle->GetComponent<TextRenderer>()->SetTextColor(glm::vec3(0.0f, 0.0f, 0.0f));

		gameTitle = new Entity("UI Title");
		gameTitle->GetTransform()->SetGlobalPosition(glm::vec3(130, 230, 1.0f));
		m_entities.push_back(gameTitle);

		gameTitle->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
				Resources::GetInstance()->GetShader("text"),
				100)
		);
		gameTitle->GetComponent<TextRenderer>()->SetTextToRender("The Mansion");
		gameTitle->GetComponent<TextRenderer>()->SetTextColor(glm::vec3(1.0f, 1.0f, 1.0f));
	}

	// Start Button
	{
		Entity* startButton = new Entity("Start Button");
		startButton->GetTransform()->SetGlobalPosition(glm::vec3(175, 375, 1.0f));
		m_entities.push_back(startButton);

		startButton->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
				Resources::GetInstance()->GetShader("text"),
				45)
		);
		startButton->GetComponent<TextRenderer>()->SetTextToRender("Start Game");
		startButton->GetComponent<TextRenderer>()->SetTextColor(glm::vec3(0.0f, 0.0f, 0.0f));

		startButton = new Entity("Start Button");
		startButton->GetTransform()->SetGlobalPosition(glm::vec3(180, 380, 1.0f));
		m_entities.push_back(startButton);

		startButton->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
				Resources::GetInstance()->GetShader("text"),
				45)
		);
		startButton->GetComponent<TextRenderer>()->SetTextToRender("Start Game");
		startButton->GetComponent<TextRenderer>()->SetTextColor(glm::vec3(1.0f, 1.0f, 1.0f));
	}

	// Options Button
	{
		Entity* optionsButton = new Entity("Options Button");
		optionsButton->GetTransform()->SetGlobalPosition(glm::vec3(175, 475, 1.0f));
		m_entities.push_back(optionsButton);

		optionsButton->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
				Resources::GetInstance()->GetShader("text"),
				45)
		);
		optionsButton->GetComponent<TextRenderer>()->SetTextToRender("Options");
		optionsButton->GetComponent<TextRenderer>()->SetTextColor(glm::vec3(0.0f, 0.0f, 0.0f));

		optionsButton = new Entity("Options Button");
		optionsButton->GetTransform()->SetGlobalPosition(glm::vec3(180, 480, 1.0f));
		m_entities.push_back(optionsButton);

		optionsButton->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
				Resources::GetInstance()->GetShader("text"),
				45)
		);
		optionsButton->GetComponent<TextRenderer>()->SetTextToRender("Options");
		optionsButton->GetComponent<TextRenderer>()->SetTextColor(glm::vec3(1.0f, 1.0f, 1.0f));
	}

	// Quit Button
	{
		Entity* quitButton = new Entity("Quit Button");
		quitButton->GetTransform()->SetGlobalPosition(glm::vec3(175, 575, 1.0f));
		m_entities.push_back(quitButton);

		quitButton->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
				Resources::GetInstance()->GetShader("text"),
				45)
		);
		quitButton->GetComponent<TextRenderer>()->SetTextToRender("Quit");
		quitButton->GetComponent<TextRenderer>()->SetTextColor(glm::vec3(0.0f, 0.0f, 0.0f));

		quitButton = new Entity("Quit Button");
		quitButton->GetTransform()->SetGlobalPosition(glm::vec3(180, 580, 1.0f));
		m_entities.push_back(quitButton);

		quitButton->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
				Resources::GetInstance()->GetShader("text"),
				45)
		);
		quitButton->GetComponent<TextRenderer>()->SetTextToRender("Quit");
		quitButton->GetComponent<TextRenderer>()->SetTextColor(glm::vec3(1.0f, 1.0f, 1.0f));
	}


	// Options Menu UI Elements
	Entity* optionsParent = new Entity("Options");
	this->m_entities.push_back(optionsParent);

	// Options Title

	// Volume Options

	// Mouse Sensitivity Options

	// Main Menu Button
}