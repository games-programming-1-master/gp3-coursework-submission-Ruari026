#include "OptionsMenuButton.h"
#include "OptionsMenuManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Entity.h"

OptionsMenuButton::OptionsMenuButton()
{
}

OptionsMenuButton::~OptionsMenuButton()
{
}


void OptionsMenuButton::OnClick()
{
	// Gets the options menu controller in the scene
	OptionsMenuManager* menuManager = SceneManager::GetInstance()->GetCurrentScene()->GetEntity("Options Menu Manager")->GetComponent<OptionsMenuManager>();

	// Checks that it exists
	if (menuManager != nullptr)
	{
		switch (buttonType)
		{
		case (OptionsMenuButtonType::BUTTONTYPE_CANCELOPTIONS):
		{
			menuManager->ReturnToMainMenu(false);
		}
		break;

		case (OptionsMenuButtonType::BUTTONTYPE_SAVEOPTIONS):
		{
			menuManager->ReturnToMainMenu(true);
		}
		break;
		}
	}
}