#pragma once
#include "Button.h"
enum class OptionsMenuButtonType
{
	BUTTONTYPE_NONE,
	BUTTONTYPE_DECREASEVOLUME,
	BUTTONTYPE_INCREASEVOLUME,
	BUTTONTYPE_DECREASESENSITIVITY,
	BUTTONTYPE_INCREASESENSITIVITY,
	BUTTONTYPE_CANCELOPTIONS,
	BUTTONTYPE_SAVEOPTIONS,
};

class OptionsMenuButton : public Button
{
private:
	OptionsMenuButtonType buttonType;

protected:
	virtual void OnClick() override;

public:
	OptionsMenuButton();
	virtual ~OptionsMenuButton() override;

	void SetButtonType(OptionsMenuButtonType newType) { buttonType = newType; }
};