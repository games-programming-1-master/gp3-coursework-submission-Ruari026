#include "TutorialButton_Prefab.h"

#include "Resources.h"

#include "TutorialMenuButton.h"
#include "ImageRenderer.h"
#include "TextRenderer.h"


TutorialButton_Prefab::TutorialButton_Prefab(std::string name, std::string text, int textIndent) : Entity(name)
{
	// Main Button
	this->AddComponent(
		new ImageRenderer(
			Resources::GetInstance()->GetTexture("Images/Textures/Button Small.png"),
			Resources::GetInstance()->GetShader("text"))
	);
	this->GetComponent<ImageRenderer>()->SetImageSize(glm::ivec2((64 * 1.25f), (64 * 1.25f)));
	this->AddComponent<TutorialMenuButton>();
	this->GetComponent<TutorialMenuButton>()->SetButtonRenderer(this->GetComponent<ImageRenderer>());

	// Overlayed Text
	Entity* buttonText = new Entity("Text");
	this->AddChild(buttonText);
	buttonText->GetTransform()->SetLocalPosition(glm::vec3(37.5f + textIndent, -25, 1.0f));

	buttonText->AddComponent(
		new TextRenderer(
			Resources::GetInstance()->GetFont("Fonts/Pixel Musketeer.ttf"),
			Resources::GetInstance()->GetShader("text"),
			45)
	);
	buttonText->GetComponent<TextRenderer>()->SetTextToRender(text);
}