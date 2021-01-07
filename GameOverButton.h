#pragma once
#include "Button.h"
enum class GameOverButtonType
{
	BUTTONTYPE_NONE,
	BUTTONTYPE_REPLAY,
	BUTTONTYPE_MAINMENU,
};

class GameOverButton : public Button
{
private:
	GameOverButtonType buttonType;

protected:
	virtual void OnClick() override;

public:
	GameOverButton();
	virtual ~GameOverButton() override;

	void SetButtonType(GameOverButtonType newType) { buttonType = newType; }
};