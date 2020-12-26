#pragma once
#include "Button.h"
enum class MainMenuButtonType
{
	BUTTONTYPE_NONE,
	BUTTONTYPE_STARTGAME,
	BUTTONTYPE_OPENOPTIONS,
	BUTTONTYPE_QUITGAME
};

class MainMenuButton : public Button
{
private:
	MainMenuButtonType buttonType;

protected:
	virtual void OnClick() override;

public:
	MainMenuButton();
	~MainMenuButton();

	void SetButtonType(MainMenuButtonType newType) { buttonType = newType; }
};