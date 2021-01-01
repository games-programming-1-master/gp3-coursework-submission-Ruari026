#pragma once
#include "Button.h"

enum class PauseMenuButtonType
{
	BUTTONTYPE_NONE,
	BUTTONTYPE_UNPAUSEGAME,
	BUTTONTYPE_RETURNTOMAINMENU,
};

class PauseMenuButton : public Button
{
private:
	PauseMenuButtonType buttonType;

protected:
	virtual void OnClick() override;

public:
	PauseMenuButton();
	virtual ~PauseMenuButton() override;

	void SetButtonType(PauseMenuButtonType newType) { buttonType = newType; }
};