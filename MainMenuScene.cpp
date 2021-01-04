#include "MainMenuScene.h"

// General Engine Includes
#include "Resources.h"

// Scene Prefabs
#include "MainMenuButton_Prefab.h"
#include "OptionsMenuButton_Normal_Prefab.h"
#include "OptionsMenuButton_Small_Prefab.h"
#include "Room_2DoorCorner_RightDown_TopFloor.h"
#include "DoorPrefab.h"

// Other Required Components
#include "TextRenderer.h"
#include "MainMenuManager.h"
#include "MainMenuButton.h"
#include "OptionsMenuManager.h"
#include "OptionsMenuButton.h"
#include "TransitionRenderer.h"

#include "RigidBody.h"
#include "BoxShape.h"
#include "MeshRenderer.h"

MainMenuScene::MainMenuScene()
{
	// ---------- General Scene Details ----------
	// Every Scene Needs A Camera
	Entity* camera = new Entity("The Camera");
	m_entities.push_back(camera);
	this->SetCamera(new Camera(camera->GetTransform()));
	camera->GetTransform()->SetLocalPosition(glm::vec3(-0.5f, 1.5f, -3.0f));
	camera->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * -1.167f), glm::vec3(0, 1, 0)));

	// Managers to control Main Menu behaviour
	Entity* mainController = new Entity("Main Menu Manager");
	m_entities.push_back(mainController);
	mainController->AddComponent<MainMenuManager>();

	Entity* optionsController = new Entity("Options Menu Manager");
	m_entities.push_back(optionsController);
	optionsController->AddComponent<OptionsMenuManager>();


	// UI Parents to enable hiding/ showing many related UI elements at once
	Entity* mainMenuParent = new Entity("Main Menu");
	this->m_entities.push_back(mainMenuParent);
	mainMenuParent->SetEnabled(true);

	Entity* optionsParent = new Entity("Options");
	this->m_entities.push_back(optionsParent);
	optionsParent->SetEnabled(false);

	mainController->GetComponent<MainMenuManager>()->SetMenuParents(mainMenuParent, optionsParent);
	optionsController->GetComponent<OptionsMenuManager>()->SetMenuParents(mainMenuParent, optionsParent);


	// ---------- Spawning Background Environment ----------
	Entity* backgroundRoom = new Room_2DoorCorner_RightDown_TopFloor("Background Room");
	m_entities.push_back(backgroundRoom);

	Entity* backgroundDoor = new DoorPrefab("Background Door");
	backgroundDoor->GetTransform()->SetGlobalPosition(glm::vec3(-9.25f, 0, 0));
	backgroundDoor->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * 0.5f), glm::vec3(0, 1, 0)));
	m_entities.push_back(backgroundDoor);

	// ---------- Main Menu Specific UI Entitys ----------
	{
		std::vector<Button*> menuButtons;

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
			menuButtons.push_back(startButton->GetComponent<Button>());
		}

		// Options Button
		{
			Entity* optionsButton = new MainMenuButton_Prefab("Options Button", "Options");
			mainMenuParent->AddChild(optionsButton);

			optionsButton->GetTransform()->SetGlobalPosition(glm::vec3(100, 515, 1.0f));

			optionsButton->GetComponent<MainMenuButton>()->SetButtonType(MainMenuButtonType::BUTTONTYPE_OPENOPTIONS);
			menuButtons.push_back(optionsButton->GetComponent<Button>());
		}

		// Quit Button
		{
			Entity* quitButton = new MainMenuButton_Prefab("Quit Button", "Quit");
			mainMenuParent->AddChild(quitButton);

			quitButton->GetTransform()->SetGlobalPosition(glm::vec3(100, 640, 1.0f));

			quitButton->GetComponent<MainMenuButton>()->SetButtonType(MainMenuButtonType::BUTTONTYPE_QUITGAME);
			menuButtons.push_back(quitButton->GetComponent<Button>());
		}

		mainController->GetComponent<MainMenuManager>()->SetMenuButtons(menuButtons);
	}


	// ---------- Options Specific UI Entitys ----------
	{
		// Options Title
		{
			Entity* optionsTitle = new Entity("Options Title");
			optionsTitle->GetTransform()->SetGlobalPosition(glm::vec3(465, 115, 1.0f));
			optionsParent->AddChild(optionsTitle);

			optionsTitle->AddComponent(
				new TextRenderer(
					Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
					Resources::GetInstance()->GetShader("text"),
					75)
			);
			optionsTitle->GetComponent<TextRenderer>()->SetTextToRender("Options");
			optionsTitle->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

			optionsTitle = new Entity("Options Title");
			optionsTitle->GetTransform()->SetGlobalPosition(glm::vec3(470, 120, 1.0f));
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
		{
			// Subtitle
			Entity* volumeTitle = new Entity("Volume Subtitle");
			volumeTitle->GetTransform()->SetGlobalPosition(glm::vec3(505, 225, 1.0f));
			optionsParent->AddChild(volumeTitle);

			volumeTitle->AddComponent(
				new TextRenderer(
					Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
					Resources::GetInstance()->GetShader("text"),
					55)
			);
			volumeTitle->GetComponent<TextRenderer>()->SetTextToRender("Volume");
			volumeTitle->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

			volumeTitle = new Entity("Volume Subtitle");
			volumeTitle->GetTransform()->SetGlobalPosition(glm::vec3(510, 230, 1.0f));
			optionsParent->AddChild(volumeTitle);

			volumeTitle->AddComponent(
				new TextRenderer(
					Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
					Resources::GetInstance()->GetShader("text"),
					55)
			);
			volumeTitle->GetComponent<TextRenderer>()->SetTextToRender("Volume");
			volumeTitle->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));


			// Value Representation
			std::vector<TextRenderer*>  volumeValueTexts;

			Entity* volumeValue = new Entity("Volume Subtitle");
			volumeValue->GetTransform()->SetGlobalPosition(glm::vec3(585, 305, 1.0f));
			optionsParent->AddChild(volumeValue);

			volumeValue->AddComponent(
				new TextRenderer(
					Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
					Resources::GetInstance()->GetShader("text"),
					55)
			);
			volumeValue->GetComponent<TextRenderer>()->SetTextToRender("X");
			volumeValue->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
			volumeValueTexts.push_back(volumeValue->GetComponent<TextRenderer>());

			volumeValue = new Entity("Volume Subtitle");
			volumeValue->GetTransform()->SetGlobalPosition(glm::vec3(590, 310, 1.0f));
			optionsParent->AddChild(volumeValue);

			volumeValue->AddComponent(
				new TextRenderer(
					Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
					Resources::GetInstance()->GetShader("text"),
					55)
			);
			volumeValue->GetComponent<TextRenderer>()->SetTextToRender("X");
			volumeValue->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			volumeValueTexts.push_back(volumeValue->GetComponent<TextRenderer>());

			optionsController->GetComponent<OptionsMenuManager>()->SetVolumeUI(volumeValueTexts);

			// Value Changing Buttons
			Entity* decreaseButton = new OptionsMenuButton_Small_Prefab("Decrease Volume Button", "<-", -15);
			optionsParent->AddChild(decreaseButton);
			decreaseButton->GetTransform()->SetGlobalPosition(glm::vec3(310, 285, 1.0f));
			decreaseButton->GetComponent<OptionsMenuButton>()->SetButtonType(OptionsMenuButtonType::BUTTONTYPE_DECREASEVOLUME);

			Entity* increaseButton = new OptionsMenuButton_Small_Prefab("Increase Volume Button", "->", -15);
			optionsParent->AddChild(increaseButton);
			increaseButton->GetTransform()->SetGlobalPosition(glm::vec3(805, 285, 1.0f));
			increaseButton->GetComponent<OptionsMenuButton>()->SetButtonType(OptionsMenuButtonType::BUTTONTYPE_INCREASEVOLUME);
		}

		// Mouse Sensitivity Options
		{
			Entity* sensitivityTitle = new Entity("Sensitivity Subtitle");
			sensitivityTitle->GetTransform()->SetGlobalPosition(glm::vec3(455, 425, 1.0f));
			optionsParent->AddChild(sensitivityTitle);

			sensitivityTitle->AddComponent(
				new TextRenderer(
					Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
					Resources::GetInstance()->GetShader("text"),
					55)
			);
			sensitivityTitle->GetComponent<TextRenderer>()->SetTextToRender("Sensitivity");
			sensitivityTitle->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

			sensitivityTitle = new Entity("Sensitivity Subtitle");
			sensitivityTitle->GetTransform()->SetGlobalPosition(glm::vec3(460, 430, 1.0f));
			optionsParent->AddChild(sensitivityTitle);

			sensitivityTitle->AddComponent(
				new TextRenderer(
					Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
					Resources::GetInstance()->GetShader("text"),
					55)
			);
			sensitivityTitle->GetComponent<TextRenderer>()->SetTextToRender("Sensitivity");
			sensitivityTitle->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));


			// Value Representation
			std::vector<TextRenderer*>  sensitivityValueTexts;

			Entity* sensitivityValue = new Entity("Volume Subtitle");
			sensitivityValue->GetTransform()->SetGlobalPosition(glm::vec3(585, 505, 1.0f));
			optionsParent->AddChild(sensitivityValue);

			sensitivityValue->AddComponent(
				new TextRenderer(
					Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
					Resources::GetInstance()->GetShader("text"),
					55)
			);
			sensitivityValue->GetComponent<TextRenderer>()->SetTextToRender("X");
			sensitivityValue->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
			sensitivityValueTexts.push_back(sensitivityValue->GetComponent<TextRenderer>());

			sensitivityValue = new Entity("Volume Subtitle");
			sensitivityValue->GetTransform()->SetGlobalPosition(glm::vec3(590, 510, 1.0f));
			optionsParent->AddChild(sensitivityValue);

			sensitivityValue->AddComponent(
				new TextRenderer(
					Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
					Resources::GetInstance()->GetShader("text"),
					55)
			);
			sensitivityValue->GetComponent<TextRenderer>()->SetTextToRender("X");
			sensitivityValue->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			sensitivityValueTexts.push_back(sensitivityValue->GetComponent<TextRenderer>());

			optionsController->GetComponent<OptionsMenuManager>()->SetSensitivityUI(sensitivityValueTexts);


			// Value Changing Buttons
			Entity* decreaseButton = new OptionsMenuButton_Small_Prefab("Decrease Volume Button", "<-", -15);
			optionsParent->AddChild(decreaseButton);
			decreaseButton->GetTransform()->SetGlobalPosition(glm::vec3(310, 485, 1.0f));
			decreaseButton->GetComponent<OptionsMenuButton>()->SetButtonType(OptionsMenuButtonType::BUTTONTYPE_DECREASESENSITIVITY);

			Entity* increaseButton = new OptionsMenuButton_Small_Prefab("Increase Volume Button", "->", -15);
			optionsParent->AddChild(increaseButton);
			increaseButton->GetTransform()->SetGlobalPosition(glm::vec3(805, 485, 1.0f));
			increaseButton->GetComponent<OptionsMenuButton>()->SetButtonType(OptionsMenuButtonType::BUTTONTYPE_INCREASESENSITIVITY);
		}

		// Return Buttons
		{
			Entity* cancelButton = new OptionsMenuButton_Normal_Prefab("cancel Button", "Cancel", 50);
			optionsParent->AddChild(cancelButton);
			cancelButton->GetTransform()->SetGlobalPosition(glm::vec3(260, 675, 1.0f));
			cancelButton->GetComponent<OptionsMenuButton>()->SetButtonType(OptionsMenuButtonType::BUTTONTYPE_CANCELOPTIONS);


			Entity* saveButton = new OptionsMenuButton_Normal_Prefab("cancel Button", "Save", 75);
			optionsParent->AddChild(saveButton);
			saveButton->GetTransform()->SetGlobalPosition(glm::vec3(660, 675, 1.0f));
			saveButton->GetComponent<OptionsMenuButton>()->SetButtonType(OptionsMenuButtonType::BUTTONTYPE_SAVEOPTIONS);
		}
	}


	// ---------- Fade In/ Out Controller ----------
	Entity* transitionController = new Entity("Transition Controller");
	transitionController->AddComponent(
		new TransitionRenderer(
			Resources::GetInstance()->GetTexture("Images/Textures/transition.png"),
			Resources::GetInstance()->GetShader("mask"))
	);
	m_entities.push_back(transitionController);
	mainController->GetComponent<MainMenuManager>()->SetTransitionController(transitionController->GetComponent<TransitionRenderer>());
	mainController->GetComponent<MainMenuManager>()->SetSceneCamera(camera);
}