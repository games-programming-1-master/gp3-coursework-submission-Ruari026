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
#include "OptionsMenuButton_Normal_Prefab.h"

// Testing out prefabs TODO: Remove before final build
#include "Room_2DoorCorner_TopFloor.h"
#include "Room_2DoorStraight_TopFloor.h"
#include "Room_3Door_TopFloor.h"

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
		camera->GetTransform()->SetLocalPosition(glm::vec3(0, 0.5f, 0));

		// Setting up the controller for the player
		player->AddComponent<PlayerController>();
		player->GetComponent<PlayerController>()->SetCameraMount(camera);
	}


	// Level Generator
	Entity* levelManager = new Entity("Level Manager");
	m_entities.push_back(levelManager);
	levelManager->AddComponent<LevelManager>();
	levelManager->AddComponent<LevelGenerator>();

	// Reuses Options Menu Manager for ease
	Entity* optionsManager = new Entity("Options Manager");
	m_entities.push_back(optionsManager);
	optionsManager->AddComponent<OptionsMenuManager>();


	// UI Parents to enable hiding/ showing many related UI elements at once
	Entity* gameplayUIParent = new Entity("Gameplay UI");
	this->m_entities.push_back(gameplayUIParent);
	gameplayUIParent->SetEnabled(false);

	Entity* pauseMenuParent = new Entity("Pause Menu");
	this->m_entities.push_back(pauseMenuParent);
	pauseMenuParent->SetEnabled(true);

	// ---------- Gameplay UI ----------
	{
		// Level Timer

		// Number of enemy's left
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
		menuBackground->GetComponent<TransitionRenderer>()->SetTransitionAlpha(0.667f);
		pauseMenuParent->AddChild(menuBackground);

		// Pause Title
		{
			Entity* pauseTitle = new Entity("Pause Title");
			pauseTitle->GetTransform()->SetGlobalPosition(glm::vec3(385, 115, 1.0f));
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
			pauseTitle->GetTransform()->SetGlobalPosition(glm::vec3(390, 120, 1.0f));
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


		// Return to main menu button
	}


	// ---------- Fade In/ Out Controller ----------
	Entity* transitionController = new Entity("Transition Controller");
	transitionController->AddComponent(
		new TransitionRenderer(
			Resources::GetInstance()->GetTexture("Images/Textures/transition.png"),
			Resources::GetInstance()->GetShader("mask"))
	);
	m_entities.push_back(transitionController);
	levelManager->GetComponent<LevelManager>()->SetTransitionController(transitionController->GetComponent<TransitionRenderer>());
}