#include "MainMenuScene.h"

// General Engine Includes
#include "Resources.h"
// Required Components
#include "TextRenderer.h"
#include "ImageRenderer.h"
#include "Button.h"
#include "MainMenuController.h"

MainMenuScene::MainMenuScene()
{
	// Every Scene Needs A Camera
	Entity* camera = new Entity("The Camera");
	m_entities.push_back(camera);
	this->SetCamera(new Camera(camera->GetTransform()));
	camera->GetTransform()->SetLocalPosition(glm::vec3(0, 0.5f, 0));

	// Manager to control Main Menu behaviour
	Entity* menuController = new Entity("The Controller");
	m_entities.push_back(menuController);
	menuController->AddComponent<MainMenuController>();

	// Spawning in the background environment

	// Main Menu UI Elements
	Entity* mainMenuParent = new Entity("Main Menu");
	this->m_entities.push_back(mainMenuParent);
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
		Entity* startButton = new Entity("Start Button");
		startButton->GetTransform()->SetGlobalPosition(glm::vec3(150, 387.5f, 1.0f));
		mainMenuParent->AddChild(startButton);
		startButton->AddComponent(
			new ImageRenderer(
				Resources::GetInstance()->GetTexture("Images/Textures/Button Default.png"),
				Resources::GetInstance()->GetShader("text"))
		);
		startButton->GetComponent<ImageRenderer>()->SetImageSize(glm::ivec2((256 * 1.25f), (64 * 1.25f)));
		startButton->AddComponent<Button>();
		startButton->GetComponent<Button>()->SetButtonRenderer(startButton->GetComponent<ImageRenderer>());

		Entity* buttonText = new Entity("Button Text");
		startButton->AddChild(buttonText);
		buttonText->GetTransform()->SetLocalPosition(glm::vec3(37.5f, -25, 1.0f));

		buttonText->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/Pixel Musketeer.ttf"),
				Resources::GetInstance()->GetShader("text"),
				45)
		);
		buttonText->GetComponent<TextRenderer>()->SetTextToRender("Start Game");
	}

	// Options Button
	{
		Entity* optionsButton = new Entity("Options Button");
		optionsButton->GetTransform()->SetGlobalPosition(glm::vec3(150, 500, 1.0f));
		mainMenuParent->AddChild(optionsButton);
		optionsButton->AddComponent(
			new ImageRenderer(
				Resources::GetInstance()->GetTexture("Images/Textures/Button Default.png"),
				Resources::GetInstance()->GetShader("text"))
		);
		optionsButton->GetComponent<ImageRenderer>()->SetImageSize(glm::ivec2((256 * 1.25f), (64 * 1.25f)));
		optionsButton->AddComponent<Button>();
		optionsButton->GetComponent<Button>()->SetButtonRenderer(optionsButton->GetComponent<ImageRenderer>());


		Entity* buttonText = new Entity("Button Text");
		optionsButton->AddChild(buttonText);
		buttonText->GetTransform()->SetLocalPosition(glm::vec3(37.5f, -25, 1.0f));

		buttonText->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/Pixel Musketeer.ttf"),
				Resources::GetInstance()->GetShader("text"),
				45)
		);
		buttonText->GetComponent<TextRenderer>()->SetTextToRender("Options");
		buttonText->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	}

	// Quit Button
	{
		Entity* quitButton = new Entity("Quit Button");
		quitButton->GetTransform()->SetGlobalPosition(glm::vec3(150, 612.5f, 1.0f));
		mainMenuParent->AddChild(quitButton);
		quitButton->AddComponent(
			new ImageRenderer(
				Resources::GetInstance()->GetTexture("Images/Textures/Button Default.png"),
				Resources::GetInstance()->GetShader("text"))
		);
		quitButton->GetComponent<ImageRenderer>()->SetImageSize(glm::ivec2((256 * 1.25f), (64 * 1.25f)));
		quitButton->AddComponent<Button>();
		quitButton->GetComponent<Button>()->SetButtonRenderer(quitButton->GetComponent<ImageRenderer>());


		Entity* buttonText = new Entity("Button Text");
		quitButton->AddChild(buttonText);
		buttonText->GetTransform()->SetLocalPosition(glm::vec3(37.5f, -25, 1.0f));

		buttonText->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/Pixel Musketeer.ttf"),
				Resources::GetInstance()->GetShader("text"),
				45)
		);
		buttonText->GetComponent<TextRenderer>()->SetTextToRender("Quit");
		buttonText->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	}

	// Options Menu UI Elements
	Entity* optionsParent = new Entity("Options");
	this->m_entities.push_back(optionsParent);
	optionsParent->SetEnabled(false);

	// Options Title

	// Volume Options

	// Mouse Sensitivity Options

	// Main Menu Button
}