#include "MainMenuScene.h"

// General Engine Includes
#include "Resources.h"

// Scene Prefabs
#include "MainMenuButton_Prefab.h"
#include "OptionsMenuButton_Prefab.h"

// Other Required Components
#include "TextRenderer.h"
#include "MainMenuManager.h"
#include "MainMenuButton.h"
#include "OptionsMenuManager.h"
#include "OptionsMenuButton.h"

MainMenuScene::MainMenuScene()
{
	// ---------- General Scene Details ----------
	// Every Scene Needs A Camera
	Entity* camera = new Entity("The Camera");
	m_entities.push_back(camera);
	this->SetCamera(new Camera(camera->GetTransform()));
	camera->GetTransform()->SetLocalPosition(glm::vec3(0, 0.5f, 0));

	// Managers to control Main Menu behaviour
	Entity* mainController = new Entity("Main Menu Manager");
	m_entities.push_back(mainController);
	mainController->AddComponent<MainMenuManager>();

	Entity* optionsController = new Entity("Options Menu Manager");
	m_entities.push_back(optionsController);
	optionsController->AddComponent<OptionsMenuManager>();


	// Parents to enable hiding/ showing many related UI elements at once
	Entity* mainMenuParent = new Entity("Main Menu");
	this->m_entities.push_back(mainMenuParent);
	mainMenuParent->SetEnabled(true);

	Entity* optionsParent = new Entity("Options");
	this->m_entities.push_back(optionsParent);
	optionsParent->SetEnabled(false);

	mainController->GetComponent<MainMenuManager>()->SetMenuParents(mainMenuParent, optionsParent);
	optionsController->GetComponent<OptionsMenuManager>()->SetMenuParents(mainMenuParent, optionsParent);

	// ---------- Spawning Background Environment ----------


	// ---------- Main Menu Specific UI Entitys ----------
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

		startButton->GetTransform()->SetGlobalPosition(glm::vec3(100, 390, 1.0f));

		startButton->GetComponent<MainMenuButton>()->SetButtonType(MainMenuButtonType::BUTTONTYPE_STARTGAME);
	}

	// Options Button
	{
		Entity* optionsButton = new MainMenuButton_Prefab("Options Button", "Options");
		mainMenuParent->AddChild(optionsButton);

		optionsButton->GetTransform()->SetGlobalPosition(glm::vec3(100, 515, 1.0f));

		optionsButton->GetComponent<MainMenuButton>()->SetButtonType(MainMenuButtonType::BUTTONTYPE_OPENOPTIONS);
	}

	// Quit Button
	{
		Entity* quitButton = new MainMenuButton_Prefab("Quit Button", "Quit");
		mainMenuParent->AddChild(quitButton);

		quitButton->GetTransform()->SetGlobalPosition(glm::vec3(100, 640, 1.0f));

		quitButton->GetComponent<MainMenuButton>()->SetButtonType(MainMenuButtonType::BUTTONTYPE_QUITGAME);
	}


	// ---------- Options Specific UI Entitys ----------
	// Options Title
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

	// Return Buttons
	{
		Entity* cancelButton = new OptionsMenuButton_Prefab("cancel Button", "Cancel", 50);
		optionsParent->AddChild(cancelButton);

		cancelButton->GetTransform()->SetGlobalPosition(glm::vec3(260, 675, 1.0f));

		cancelButton->GetComponent<OptionsMenuButton>()->SetButtonType(OptionsMenuButtonType::BUTTONTYPE_CANCELOPTIONS);


		Entity* saveButton = new OptionsMenuButton_Prefab("cancel Button", "Save", 75);
		optionsParent->AddChild(saveButton);

		saveButton->GetTransform()->SetGlobalPosition(glm::vec3(660, 675, 1.0f));

		saveButton->GetComponent<OptionsMenuButton>()->SetButtonType(OptionsMenuButtonType::BUTTONTYPE_SAVEOPTIONS);
	}
}