#include "TutorialMenuButton.h"
#include "TutorialManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Entity.h"

TutorialMenuButton::TutorialMenuButton()
{
}

TutorialMenuButton::~TutorialMenuButton()
{
}


void TutorialMenuButton::OnClick()
{
	// Gets the options menu controller in the scene
	TutorialManager* menuManager = SceneManager::GetInstance()->GetCurrentScene()->GetEntity("Tutorial Manager")->GetComponent<TutorialManager>();

	// Checks that it exists
	if (menuManager != nullptr)
	{
		switch (buttonType)
		{
		case (TutorialButtonType::BUTTONTYPE_SHOWCONTROLS):
		{
			menuManager->OpenControls();
		}
		break;

		case (TutorialButtonType::BUTTONTYPE_STARTNEXTLEVEL):
		{
			menuManager->MoveToGame();
		}
		break;
		}
	}
}