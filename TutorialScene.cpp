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
		Entity* gameStory = new Entity("UI Title");
		gameStory->GetTransform()->SetGlobalPosition(glm::vec3(125, 225, 1.0f));
		m_entities.push_back(gameStory);

		gameStory->AddComponent(
			new TextRenderer(
				Resources::GetInstance()->GetFont("Fonts/JMH Cthulhumbus Arcade UG.ttf"),
				Resources::GetInstance()->GetShader("text"),
				55)
		);
		gameStory->GetComponent<TextRenderer>()->SetTextToRender("Story");
		gameStory->GetComponent<TextRenderer>()->SetTextColor(glm::vec4(0.88f, 0.88f, 0.88f, 1.0f));
	}
	
	// Controls Text
	{

	}

	// Objective Text
	{

	}
}