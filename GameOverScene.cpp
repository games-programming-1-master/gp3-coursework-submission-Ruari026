#include "GameOverScene.h"

// General Engine Includes
#include "Resources.h"

// Required Components
#include "TextRenderer.h"
#include "GameOverManager.h"
#include "GameOverButton.h"

// Required Prefab
#include "GameOverButton_Prefab.h"

GameOverScene::GameOverScene()
{
	// ----------General Scene Details----------
	// Every Scene Needs A Camera
	Entity* camera = new Entity("The Camera");
	m_entities.push_back(camera);
	this->SetCamera(new Camera(camera->GetTransform()));
	camera->GetTransform()->SetLocalPosition(glm::vec3(0, 0.5f, 0));

	// Changing Background Color
	this->clearColor = glm::vec4(0.09f, 0.09f, 0.09f, 1.0f);

	// Scene Manager
	Entity* sceneController = new Entity("Game Over Manager");
	sceneController->AddComponent<GameOverManager>();
	m_entities.push_back(sceneController);


	// ----------Story End----------
	{
		Entity* title = new Entity("Title");
		title->GetTransform()->SetGlobalPosition(glm::vec3(450, 100, 1.0f));
		m_entities.push_back(title);

		title->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
				Resources::GetInstance()->GetShader("text"),
				55)
		);
		title->GetComponent<TextRenderer>()->SetTextToRender("GAME OVER");
		title->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.88f, 0.88f, 0.88f, 1.0f));


		Entity* storyText = new Entity("Story Text (1)");
		storyText->GetTransform()->SetGlobalPosition(glm::vec3(175, 170, 1.0f));
		m_entities.push_back(storyText);

		storyText->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/PixelNoise_erc_2007.ttf"),
				Resources::GetInstance()->GetShader("text"),
				110)
		);
		storyText->GetComponent<TextRenderer>()->SetTextToRender("This place... it traps us all. I am doomed to remain here forever...");
		storyText->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.88f, 0.88f, 0.88f, 1.0f));
		storyText->GetComponent<TextRenderer>()->SetTextBoxWidth(905);


		storyText = new Entity("Story Text (2)");
		storyText->GetTransform()->SetGlobalPosition(glm::vec3(175, 300, 1.0f));
		m_entities.push_back(storyText);

		storyText->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/PixelNoise_erc_2007.ttf"),
				Resources::GetInstance()->GetShader("text"),
				110)
		);
		storyText->GetComponent<TextRenderer>()->SetTextToRender("I hope the next visitor is wiser than I was and decides to just leave...");
		storyText->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.88f, 0.88f, 0.88f, 1.0f));
		storyText->GetComponent<TextRenderer>()->SetTextBoxWidth(905);
	}


	// ----------Gameplay Stats----------
	{
		Entity* levelStats = new Entity("Stats Text (1)");
		levelStats->GetTransform()->SetGlobalPosition(glm::vec3(175, 470, 1.0f));
		m_entities.push_back(levelStats);

		levelStats->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/PixelNoise_erc_2007.ttf"),
				Resources::GetInstance()->GetShader("text"),
				110)
		);
		levelStats->GetComponent<TextRenderer>()->SetTextToRender("You made it through XX Floors & Killed XX Ghosts");
		levelStats->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.88f, 0.88f, 0.88f, 1.0f));
		sceneController->GetComponent<GameOverManager>()->SetGameStatsText(levelStats->GetComponent<TextRenderer>());

		Entity* GameStatsEnd = new Entity("Stats Title");
		GameStatsEnd->GetTransform()->SetGlobalPosition(glm::vec3(225, 550, 1.0f));
		m_entities.push_back(GameStatsEnd);

		GameStatsEnd->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/PixelNoise_erc_2007.ttf"),
				Resources::GetInstance()->GetShader("text"),
				110)
		);
		GameStatsEnd->GetComponent<TextRenderer>()->SetTextToRender("Before you were consumed by The Mansion");
		GameStatsEnd->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.88f, 0.88f, 0.88f, 1.0f));
	}


	// ----------Level Exit Buttons----------
	{
		std::vector<Button*> sceneButtons;

		Entity* cancelButton = new GameOverButton_Prefab("Replay Button", "Replay", 50);
		m_entities.push_back(cancelButton);
		cancelButton->GetTransform()->SetGlobalPosition(glm::vec3(260, 675, 1.0f));
		cancelButton->GetComponent<GameOverButton>()->SetButtonType(GameOverButtonType::BUTTONTYPE_REPLAY);
		sceneButtons.push_back(cancelButton->GetComponent<Button>());

		Entity* menuButton = new GameOverButton_Prefab("Main Menu Button", "Main Menu", 10);
		m_entities.push_back(menuButton);
		menuButton->GetTransform()->SetGlobalPosition(glm::vec3(660, 675, 1.0f));
		menuButton->GetComponent<GameOverButton>()->SetButtonType(GameOverButtonType::BUTTONTYPE_MAINMENU);
		sceneButtons.push_back(menuButton->GetComponent<Button>());

		sceneController->GetComponent<GameOverManager>()->SetSceneButtons(sceneButtons);
	}


	// ---------- Fade In/ Out Controller ----------
	Entity* transitionController = new Entity("Transition Controller");
	transitionController->AddComponent(
		new TransitionRenderer(
			Resources::GetInstance()->GetTexture("Images/Textures/transition.png"),
			Resources::GetInstance()->GetShader("mask"))
	);
	m_entities.push_back(transitionController);
	sceneController->GetComponent<GameOverManager>()->SetTransitionController(transitionController->GetComponent<TransitionRenderer>());
}