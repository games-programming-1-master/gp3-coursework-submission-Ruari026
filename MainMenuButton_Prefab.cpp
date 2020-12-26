#include "MainMenuButton_Prefab.h"

#include "Resources.h"

#include "MainMenuButton.h"
#include "ImageRenderer.h"
#include "TextRenderer.h"


MainMenuButton_Prefab::MainMenuButton_Prefab(std::string name, std::string text) : Entity(name)
{
	// Main Button
	this->AddComponent(
		new ImageRenderer(
			Resources::GetInstance()->GetTexture("Images/Textures/Button Default.png"),
			Resources::GetInstance()->GetShader("text"))
	);
	this->GetComponent<ImageRenderer>()->SetImageSize(glm::ivec2((256 * 1.25f), (64 * 1.25f)));
	this->AddComponent<MainMenuButton>();
	this->GetComponent<MainMenuButton>()->SetButtonRenderer(this->GetComponent<ImageRenderer>());

	// Overlayed Text (based on button name for simplicity
	Entity* buttonText = new Entity("Text");
	this->AddChild(buttonText);
	buttonText->GetTransform()->SetLocalPosition(glm::vec3(37.5f, -25, 1.0f));

	buttonText->AddComponent(
		new TextRenderer(
			Resources::GetInstance()->GetFont("Fonts/Pixel Musketeer.ttf"),
			Resources::GetInstance()->GetShader("text"),
			45)
	);
	buttonText->GetComponent<TextRenderer>()->SetTextToRender(text);
}