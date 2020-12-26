#include "MainMenuScene.h"

// General Engine Includes
#include "Resources.h"

// Scene Prefabs
#include "MainMenuButton_Prefab.h"

// Other Required Components
#include "TextRenderer.h"
#include "ImageRenderer.h"
#include "MainMenuButton.h"
#include "MainMenuManager.h"

MainMenuScene::MainMenuScene()
{
	// Every Scene Needs A Camera
	Entity* camera = new Entity("The Camera");
	m_entities.push_back(camera);
	this->SetCamera(new Camera(camera->GetTransform()));
	camera->GetTransform()->SetLocalPosition(glm::vec3(0, 0.5f, 0));

	// Manager to control Main Menu behaviour
	Entity* menuController = new Entity("Main Menu Controller");
	m_entities.push_back(menuController);
	menuController->AddComponent<MainMenuManager>();

	// Spawning in the background environment

	// Main Menu UI Elements
	Entity* mainMenuParent = new Entity("Main Menu");
	this->m_entities.push_back(mainMenuParent);
	mainMenuParent->SetEnabled(false);
	// Game Title
	{
		Entity* gameTitle = new Entity("UI Title");
		gameTitle->GetTransform()->SetGlobalPosition(glm::vec3(125, 225, 1.0f));
		mainMenuParent->AddChild(gameTitle);

		gameTitle->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
				Resources::GetInstance()->GetShader("text"),
				100)
		);
		gameTitle->GetComponent<TextRenderer>()->SetTextToRender("THE MANSION");
		gameTitle->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

		gameTitle = new Entity("UI Title");
		gameTitle->GetTransform()->SetGlobalPosition(glm::vec3(130, 230, 1.0f));
		mainMenuParent->AddChild(gameTitle);

		gameTitle->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
				Resources::GetInstance()->GetShader("text"),
				100)
		);
		gameTitle->GetComponent<TextRenderer>()->SetTextToRender("THE MANSION");
		gameTitle->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	}

	// Start Button
	{
		Entity* startButton = new MainMenuButton_Prefab("Start Button", "Start Game");
		mainMenuParent->AddChild(startButton);

		startButton->GetTransform()->SetGlobalPosition(glm::vec3(150, 387.5f, 1.0f));

		startButton->GetComponent<MainMenuButton>()->SetButtonType(MainMenuButtonType::BUTTONTYPE_STARTGAME);
	}

	// Options Button
	{
		Entity* optionsButton = new MainMenuButton_Prefab("Options Button", "Options");
		mainMenuParent->AddChild(optionsButton);

		optionsButton->GetTransform()->SetGlobalPosition(glm::vec3(150, 500, 1.0f));

		optionsButton->GetComponent<MainMenuButton>()->SetButtonType(MainMenuButtonType::BUTTONTYPE_OPENOPTIONS);
	}

	// Quit Button
	{
		Entity* quitButton = new MainMenuButton_Prefab("Quit Button", "Quit");
		mainMenuParent->AddChild(quitButton);

		quitButton->GetTransform()->SetGlobalPosition(glm::vec3(150, 612.5f, 1.0f));

		quitButton->GetComponent<MainMenuButton>()->SetButtonType(MainMenuButtonType::BUTTONTYPE_QUITGAME);
	}

	// Options Menu UI Elements
	Entity* optionsParent = new Entity("Options");
	this->m_entities.push_back(optionsParent);
	optionsParent->SetEnabled(true);


	// Game Title
	{
		Entity* optionsTitle = new Entity("Options Title");
		optionsTitle->GetTransform()->SetGlobalPosition(glm::vec3(465, 150, 1.0f));
		optionsParent->AddChild(optionsTitle);

		optionsTitle->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
				Resources::GetInstance()->GetShader("text"),
				75)
		);
		optionsTitle->GetComponent<TextRenderer>()->SetTextToRender("Options");
		optionsTitle->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

		optionsTitle = new Entity("UI Title");
		optionsTitle->GetTransform()->SetGlobalPosition(glm::vec3(470, 155, 1.0f));
		optionsParent->AddChild(optionsTitle);

		optionsTitle->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
				Resources::GetInstance()->GetShader("text"),
				75)
		);
		optionsTitle->GetComponent<TextRenderer>()->SetTextToRender("Options");
		optionsTitle->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	}

	// Volume Options

	// Mouse Sensitivity Options

	// Main Menu Buttons
}