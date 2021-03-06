#include "TutorialScene.h"

// General Engine Includes
#include "Resources.h"

// Scene Prefabs
#include "TutorialButton_Prefab.h"

// Required Components
#include "TextRenderer.h"
#include "TutorialManager.h"
#include "TutorialMenuButton.h"

TutorialScene::TutorialScene()
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
	Entity* sceneController = new Entity("Tutorial Manager");
	sceneController->AddComponent<TutorialManager>();
	m_entities.push_back(sceneController);

	// Parents to enable hiding/ showing many related UI elements at once
	Entity* controlsParent = new Entity("Controls");
	this->m_entities.push_back(controlsParent);
	controlsParent->SetEnabled(false);

	Entity* story1Parent = new Entity("Story (1)");
	this->m_entities.push_back(story1Parent);
	story1Parent->SetEnabled(false);

	Entity* story2Parent = new Entity("Story (2)");
	this->m_entities.push_back(story2Parent);
	story2Parent->SetEnabled(false);

	Entity* story3Parent = new Entity("Story (3)");
	this->m_entities.push_back(story3Parent);
	story3Parent->SetEnabled(false);

	sceneController->GetComponent<TutorialManager>()->SetSceneParents(controlsParent, story1Parent, story2Parent, story3Parent);

	// ---------- Tutorial UI ----------

	// ---------- Story + Objective UI (1st Instance) ----------
	{
		Entity* storyTitle = new Entity("Story Title");
		storyTitle->GetTransform()->SetGlobalPosition(glm::vec3(125, 100, 1.0f));
		story1Parent->AddChild(storyTitle);

		storyTitle->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
				Resources::GetInstance()->GetShader("text"),
				55)
		);
		storyTitle->GetComponent<TextRenderer>()->SetTextToRender("Story :");
		storyTitle->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.88f, 0.88f, 0.88f, 1.0f));


		Entity* storyText = new Entity("Story Text (1)");
		storyText->GetTransform()->SetGlobalPosition(glm::vec3(175, 170, 1.0f));
		story1Parent->AddChild(storyText);

		storyText->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/PixelNoise_erc_2007.ttf"),
				Resources::GetInstance()->GetShader("text"),
				110)
		);
		storyText->GetComponent<TextRenderer>()->SetTextToRender("This is the biggest job I've ever attempted, This  place is notorious for having a couple of ghosts.");
		storyText->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.88f, 0.88f, 0.88f, 1.0f));
		storyText->GetComponent<TextRenderer>()->SetTextBoxWidth(875);


		storyText = new Entity("Story Text (2)");
		storyText->GetTransform()->SetGlobalPosition(glm::vec3(175, 300, 1.0f));
		story1Parent->AddChild(storyText);

		storyText->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/PixelNoise_erc_2007.ttf"),
				Resources::GetInstance()->GetShader("text"),
				110)
		);
		storyText->GetComponent<TextRenderer>()->SetTextToRender("Why hasn't anyone cleared this place out yet? Ahwell this could be my big break.....");
		storyText->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.88f, 0.88f, 0.88f, 1.0f));
		storyText->GetComponent<TextRenderer>()->SetTextBoxWidth(875);
	
		// Current Objective
		Entity* objectiveTitle = new Entity("Objective Title");
		objectiveTitle->GetTransform()->SetGlobalPosition(glm::vec3(125, 500, 1.0f));
		story1Parent->AddChild(objectiveTitle);

		objectiveTitle->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
				Resources::GetInstance()->GetShader("text"),
				55)
		);
		objectiveTitle->GetComponent<TextRenderer>()->SetTextToRender("Current Objectives :");
		objectiveTitle->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.88f, 0.88f, 0.88f, 1.0f));


		Entity* objectiveText = new Entity("Objective Text (1)");
		objectiveText->GetTransform()->SetGlobalPosition(glm::vec3(175, 570, 1.0f));
		story1Parent->AddChild(objectiveText);

		objectiveText->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/PixelNoise_erc_2007.ttf"),
				Resources::GetInstance()->GetShader("text"),
				110)
		);
		objectiveText->GetComponent<TextRenderer>()->SetTextToRender("- Explore the mansion");
		objectiveText->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.88f, 0.88f, 0.88f, 1.0f));

		objectiveText = new Entity("Objective Text (2)");
		objectiveText->GetTransform()->SetGlobalPosition(glm::vec3(175, 645, 1.0f));
		story1Parent->AddChild(objectiveText);

		objectiveText->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/PixelNoise_erc_2007.ttf"),
				Resources::GetInstance()->GetShader("text"),
				110)
		);
		objectiveText->GetComponent<TextRenderer>()->SetTextToRender("- Find and kill all of the ghosts");
		objectiveText->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.88f, 0.88f, 0.88f, 1.0f));
	}

	// ---------- Story + Objective UI (2nd Instance) ----------
	{
		Entity* storyTitle = new Entity("Story Title");
		storyTitle->GetTransform()->SetGlobalPosition(glm::vec3(125, 100, 1.0f));
		story2Parent->AddChild(storyTitle);

		storyTitle->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
				Resources::GetInstance()->GetShader("text"),
				55)
		);
		storyTitle->GetComponent<TextRenderer>()->SetTextToRender("Story Continued:");
		storyTitle->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.88f, 0.88f, 0.88f, 1.0f));


		Entity* storyText = new Entity("Story Text (1)");
		storyText->GetTransform()->SetGlobalPosition(glm::vec3(175, 170, 1.0f));
		story2Parent->AddChild(storyText);

		storyText->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/PixelNoise_erc_2007.ttf"),
				Resources::GetInstance()->GetShader("text"),
				110)
		);
		storyText->GetComponent<TextRenderer>()->SetTextToRender("This place is far bigger than I expected. This job  might take longer than I expected.");
		storyText->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.88f, 0.88f, 0.88f, 1.0f));
		storyText->GetComponent<TextRenderer>()->SetTextBoxWidth(875);


		storyText = new Entity("Story Text (2)");
		storyText->GetTransform()->SetGlobalPosition(glm::vec3(175, 300, 1.0f));
		story2Parent->AddChild(storyText);

		storyText->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/PixelNoise_erc_2007.ttf"),
				Resources::GetInstance()->GetShader("text"),
				110)
		);
		storyText->GetComponent<TextRenderer>()->SetTextToRender("Have I seen that room before... Nah I must be    imagining things...");
		storyText->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.88f, 0.88f, 0.88f, 1.0f));
		storyText->GetComponent<TextRenderer>()->SetTextBoxWidth(875);

		// Current Objective
		Entity* objectiveTitle = new Entity("Objective Title");
		objectiveTitle->GetTransform()->SetGlobalPosition(glm::vec3(125, 500, 1.0f));
		story2Parent->AddChild(objectiveTitle);

		objectiveTitle->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
				Resources::GetInstance()->GetShader("text"),
				55)
		);
		objectiveTitle->GetComponent<TextRenderer>()->SetTextToRender("Current Objectives :");
		objectiveTitle->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.88f, 0.88f, 0.88f, 1.0f));


		Entity* objectiveText = new Entity("Objective Text (1)");
		objectiveText->GetTransform()->SetGlobalPosition(glm::vec3(175, 570, 1.0f));
		story2Parent->AddChild(objectiveText);

		objectiveText->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/PixelNoise_erc_2007.ttf"),
				Resources::GetInstance()->GetShader("text"),
				110)
		);
		objectiveText->GetComponent<TextRenderer>()->SetTextToRender("- Continue to explore the Mansion");
		objectiveText->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.88f, 0.88f, 0.88f, 1.0f));

		objectiveText = new Entity("Objective Text (2)");
		objectiveText->GetTransform()->SetGlobalPosition(glm::vec3(175, 645, 1.0f));
		story2Parent->AddChild(objectiveText);

		objectiveText->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/PixelNoise_erc_2007.ttf"),
				Resources::GetInstance()->GetShader("text"),
				110)
		);
		objectiveText->GetComponent<TextRenderer>()->SetTextToRender("- There are even more ghosts now, so be careful");
		objectiveText->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.88f, 0.88f, 0.88f, 1.0f));
	}

	// ---------- Story + Objective UI (Final Instance) ----------
	{
		Entity* storyTitle = new Entity("Story Title");
		storyTitle->GetTransform()->SetGlobalPosition(glm::vec3(125, 100, 1.0f));
		story3Parent->AddChild(storyTitle);

		storyTitle->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
				Resources::GetInstance()->GetShader("text"),
				55)
		);
		storyTitle->GetComponent<TextRenderer>()->SetTextToRender("Story Continued:");
		storyTitle->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.88f, 0.88f, 0.88f, 1.0f));


		Entity* storyText = new Entity("Story Text (1)");
		storyText->GetTransform()->SetGlobalPosition(glm::vec3(175, 170, 1.0f));
		story3Parent->AddChild(storyText);

		storyText->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/PixelNoise_erc_2007.ttf"),
				Resources::GetInstance()->GetShader("text"),
				110)
		);
		storyText->GetComponent<TextRenderer>()->SetTextToRender("There's too may ghosts here, I need to get out of here...");
		storyText->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.88f, 0.88f, 0.88f, 1.0f));
		storyText->GetComponent<TextRenderer>()->SetTextBoxWidth(875);


		storyText = new Entity("Story Text (2)");
		storyText->GetTransform()->SetGlobalPosition(glm::vec3(175, 300, 1.0f));
		story3Parent->AddChild(storyText);

		storyText->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/PixelNoise_erc_2007.ttf"),
				Resources::GetInstance()->GetShader("text"),
				110)
		);
		storyText->GetComponent<TextRenderer>()->SetTextToRender("I was a fool to think I could handle this place");
		storyText->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.88f, 0.88f, 0.88f, 1.0f));
		storyText->GetComponent<TextRenderer>()->SetTextBoxWidth(875);

		// Current Objective
		Entity* objectiveTitle = new Entity("Objective Title");
		objectiveTitle->GetTransform()->SetGlobalPosition(glm::vec3(125, 500, 1.0f));
		story3Parent->AddChild(objectiveTitle);

		objectiveTitle->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
				Resources::GetInstance()->GetShader("text"),
				55)
		);
		objectiveTitle->GetComponent<TextRenderer>()->SetTextToRender("Current Objectives :");
		objectiveTitle->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.88f, 0.88f, 0.88f, 1.0f));


		Entity* objectiveText = new Entity("Objective Text (1)");
		objectiveText->GetTransform()->SetGlobalPosition(glm::vec3(175, 570, 1.0f));
		story3Parent->AddChild(objectiveText);

		objectiveText->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/PixelNoise_erc_2007.ttf"),
				Resources::GetInstance()->GetShader("text"),
				110)
		);
		objectiveText->GetComponent<TextRenderer>()->SetTextToRender("- Try to find a way out of the mansion");
		objectiveText->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.88f, 0.88f, 0.88f, 1.0f));

		objectiveText = new Entity("Objective Text (2)");
		objectiveText->GetTransform()->SetGlobalPosition(glm::vec3(175, 645, 1.0f));
		story3Parent->AddChild(objectiveText);

		objectiveText->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/PixelNoise_erc_2007.ttf"),
				Resources::GetInstance()->GetShader("text"),
				110)
		);
		objectiveText->GetComponent<TextRenderer>()->SetTextToRender("- Escape if you can");
		objectiveText->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.88f, 0.88f, 0.88f, 1.0f));
	}

	// Continue Button
	{
		Entity* gameButton = new TutorialButton_Prefab("Button", "->", -15);
		this->m_entities.push_back(gameButton);

		gameButton->GetTransform()->SetGlobalPosition(glm::vec3(1100, 640, 1.0f));

		gameButton->GetComponent<TutorialMenuButton>()->SetButtonType(TutorialButtonType::BUTTONTYPE_STARTNEXTLEVEL);
	}


	// ---------- Fade In/ Out Controller ----------
	Entity* transitionController = new Entity("Transition Controller");
	transitionController->AddComponent(
		new TransitionRenderer(
			Resources::GetInstance()->GetTexture("Images/Textures/transition.png"),
			Resources::GetInstance()->GetShader("mask"))
	);
	m_entities.push_back(transitionController);
	sceneController->GetComponent<TutorialManager>()->SetTransitionController(transitionController->GetComponent<TransitionRenderer>());
}