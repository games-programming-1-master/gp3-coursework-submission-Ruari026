#include "GameplayScene.h"
// General Engine Includes
#include "Resources.h"
// Required Components
#include "LevelGenerator.h"
#include "LevelManager.h"
#include "OptionsMenuManager.h"
#include "RigidBody.h"
#include "PlayerController.h"
#include "MeshRenderer.h"
#include "TransitionRenderer.h"

// Required Colliders
#include "BoxShape.h"
#include "CapsuleShape.h"

// Required prefabs
#include "PauseMenuButton.h"
#include "PauseMenuButton_Prefab.h"

GameplayScene::GameplayScene()
{
	// Setting up player character
	{
		Entity* player = new Entity("Main Player");
		m_entities.push_back(player);
		player->GetTransform()->SetGlobalPosition(glm::vec3(0.0f, 3.0f, 0.0f));

		player->AddComponent<RigidBody>();
		player->GetComponent<RigidBody>()->Init(new CapsuleShape(0.5f, 1.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
		player->GetComponent<RigidBody>()->Get()->setMassProps(1, btVector3());

		// Every scene needs a camera
		Entity* camera = new Entity("The Camera");
		player->AddChild(camera);
		this->SetCamera(new Camera(camera->GetTransform()));
		camera->GetTransform()->SetLocalPosition(glm::vec3(0, 0.75f, 0));

		// Adding "Player Weapon"
		Entity* playerPan = new Entity("The Pan");
		camera->AddChild(playerPan);
		playerPan->GetTransform()->SetLocalPosition(glm::vec3(0.1f, -0.15f, -0.125f));

		playerPan->AddComponent(
			new MeshRenderer(
				Resources::GetInstance()->GetModel("Models/Pan.obj"),
				Resources::GetInstance()->GetShader("simple"),
				Resources::GetInstance()->GetTexture("Images/Textures/Tartan.png"))
		);

		// Setting up the controller for the player
		player->AddComponent<PlayerController>();
		player->GetComponent<PlayerController>()->SetCameraMount(camera);
	}


	// Level Generator
	Entity* levelManager = new Entity("Level Manager");
	m_entities.push_back(levelManager);
	levelManager->AddComponent<LevelManager>();
	levelManager->AddComponent<LevelGenerator>();

	// UI Parents to enable hiding/ showing many related UI elements at once
	Entity* gameplayUIParent = new Entity("Gameplay UI");
	this->m_entities.push_back(gameplayUIParent);
	gameplayUIParent->SetEnabled(true);

	Entity* pauseMenuParent = new Entity("Pause Menu");
	this->m_entities.push_back(pauseMenuParent);
	pauseMenuParent->SetEnabled(false);

	levelManager->GetComponent<LevelManager>()->SetSceneParents(gameplayUIParent, pauseMenuParent);

	// ---------- Gameplay UI ----------
	{
		// Level Timer
		{
			std::vector<TextRenderer*> timerTexts;

			Entity* levelTimer = new Entity("Level Timer");
			levelTimer->GetTransform()->SetGlobalPosition(glm::vec3(580, 100, 0));
			levelTimer->AddComponent(
				new TextRenderer(
					Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
					Resources::GetInstance()->GetShader("text"),
					75)
			);

			levelTimer->GetComponent<TextRenderer>()->SetTextToRender("XXX");
			levelTimer->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0, 0, 0, 1));
			timerTexts.push_back(levelTimer->GetComponent<TextRenderer>());
			gameplayUIParent->AddChild(levelTimer);

			levelTimer = new Entity("Level Timer");
			levelTimer->GetTransform()->SetGlobalPosition(glm::vec3(585, 105, 0));
			levelTimer->AddComponent(
				new TextRenderer(
					Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
					Resources::GetInstance()->GetShader("text"),
					75)
			);
			levelTimer->GetComponent<TextRenderer>()->SetTextToRender("XXX");
			levelTimer->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(1, 1, 1, 1));
			timerTexts.push_back(levelTimer->GetComponent<TextRenderer>());
			gameplayUIParent->AddChild(levelTimer);

			levelManager->GetComponent<LevelManager>()->SetSceneTimerUI(timerTexts);
		}


		// Number of enemy's left
		{
			std::vector<TextRenderer*> mimicsTexts;

			Entity* levelMimics = new Entity("Ghosts UI");
			levelMimics->GetTransform()->SetGlobalPosition(glm::vec3(420, 150, 0));
			levelMimics->AddComponent(
				new TextRenderer(
					Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
					Resources::GetInstance()->GetShader("text"),
					33)
			);

			levelMimics->GetComponent<TextRenderer>()->SetTextToRender("Mimics Remaining: XX");
			levelMimics->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0, 0, 0, 1));
			mimicsTexts.push_back(levelMimics->GetComponent<TextRenderer>());
			gameplayUIParent->AddChild(levelMimics);

			levelMimics = new Entity("Ghosts UI");
			levelMimics->GetTransform()->SetGlobalPosition(glm::vec3(425, 155, 0));
			levelMimics->AddComponent(
				new TextRenderer(
					Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
					Resources::GetInstance()->GetShader("text"),
					33)
			);
			levelMimics->GetComponent<TextRenderer>()->SetTextToRender("Mimics Remaining: XX");
			levelMimics->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(1, 1, 1, 1));
			mimicsTexts.push_back(levelMimics->GetComponent<TextRenderer>());
			gameplayUIParent->AddChild(levelMimics);

			levelManager->GetComponent<LevelManager>()->SetSceneGhostsUI(mimicsTexts);
		}
	}


	// ---------- Pause Menu UI ----------
	{
		// Background
		Entity* menuBackground = new Entity("Menu Background");
		menuBackground->AddComponent(
			new TransitionRenderer(
				Resources::GetInstance()->GetTexture("Images/Textures/transition.png"),
				Resources::GetInstance()->GetShader("mask"))
		);
		menuBackground->GetComponent<TransitionRenderer>()->SetTransitionAlpha(0.8f);
		pauseMenuParent->AddChild(menuBackground);

		// Pause Title
		{
			Entity* pauseTitle = new Entity("Pause Title");
			pauseTitle->GetTransform()->SetGlobalPosition(glm::vec3(385, 215, 1.0f));
			pauseMenuParent->AddChild(pauseTitle);

			pauseTitle->AddComponent(
				new TextRenderer(
					Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
					Resources::GetInstance()->GetShader("text"),
					75)
			);
			pauseTitle->GetComponent<TextRenderer>()->SetTextToRender("Game Paused");
			pauseTitle->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

			pauseTitle = new Entity("Pause Title");
			pauseTitle->GetTransform()->SetGlobalPosition(glm::vec3(390, 220, 1.0f));
			pauseMenuParent->AddChild(pauseTitle);

			pauseTitle->AddComponent(
				new TextRenderer(
					Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
					Resources::GetInstance()->GetShader("text"),
					75)
			);
			pauseTitle->GetComponent<TextRenderer>()->SetTextToRender("Game Paused");
			pauseTitle->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		// Return to gameplay button
		{
			Entity* unpauseButton = new PauseMenuButton_Prefab("Unpause Button", "Resume", 47);
			pauseMenuParent->AddChild(unpauseButton);

			unpauseButton->GetTransform()->SetGlobalPosition(glm::vec3(475, 390, 1.0f));

			unpauseButton->GetComponent<PauseMenuButton>()->SetButtonType(PauseMenuButtonType::BUTTONTYPE_UNPAUSEGAME);
		}

		// Return to main menu button
		{
			Entity* mainMenuButton = new PauseMenuButton_Prefab("Main Menu Button", "Main Menu", 12);
			pauseMenuParent->AddChild(mainMenuButton);

			mainMenuButton->GetTransform()->SetGlobalPosition(glm::vec3(475, 540, 1.0f));

			mainMenuButton->GetComponent<PauseMenuButton>()->SetButtonType(PauseMenuButtonType::BUTTONTYPE_RETURNTOMAINMENU);
		}
	}


	// ---------- Fade In/ Out Controller ----------
	{
		Entity* transitionController = new Entity("Transition Controller");
		transitionController->AddComponent(
			new TransitionRenderer(
				Resources::GetInstance()->GetTexture("Images/Textures/transition.png"),
				Resources::GetInstance()->GetShader("mask"))
		);
		m_entities.push_back(transitionController);
		levelManager->GetComponent<LevelManager>()->SetTransitionController(transitionController->GetComponent<TransitionRenderer>());
	}
}