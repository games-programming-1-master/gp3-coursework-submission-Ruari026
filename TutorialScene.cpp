#include "TutorialScene.h"

// General Engine Includes
#include "Resources.h"
// Required Components
#include "TextRenderer.h"

TutorialScene::TutorialScene()
{
	// Every Scene Needs A Camera
	Entity* camera = new Entity("The Camera");
	m_entities.push_back(camera);
	this->SetCamera(new Camera(camera->GetTransform()));
	camera->GetTransform()->SetLocalPosition(glm::vec3(0, 0.5f, 0));

	// Changing Background Color
	this->clearColor = glm::vec4(0.09f, 0.09f, 0.09f, 1.0f);

	// Tutorial Scene UI

	// Story Text
	{
		Entity* storyTitle = new Entity("Story Title");
		storyTitle->GetTransform()->SetGlobalPosition(glm::vec3(125, 100, 1.0f));
		m_entities.push_back(storyTitle);

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
		m_entities.push_back(storyText);

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
		m_entities.push_back(storyText);

		storyText->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/PixelNoise_erc_2007.ttf"),
				Resources::GetInstance()->GetShader("text"),
				110)
		);
		storyText->GetComponent<TextRenderer>()->SetTextToRender("Why hasn't anyone cleared this place out yet? Ahwell this could be my big break.....");
		storyText->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.88f, 0.88f, 0.88f, 1.0f));
		storyText->GetComponent<TextRenderer>()->SetTextBoxWidth(875);
	}

	// Current Objective
	{
		Entity* objectiveTitle = new Entity("Objective Title");
		objectiveTitle->GetTransform()->SetGlobalPosition(glm::vec3(125, 500, 1.0f));
		m_entities.push_back(objectiveTitle);

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
		m_entities.push_back(objectiveText);

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
		m_entities.push_back(objectiveText);

		objectiveText->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/PixelNoise_erc_2007.ttf"),
				Resources::GetInstance()->GetShader("text"),
				110)
		);
		objectiveText->GetComponent<TextRenderer>()->SetTextToRender("- Find and kill all of the ghosts");
		objectiveText->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.88f, 0.88f, 0.88f, 1.0f));
	}

	// Continue Button
	{

	}
}