#pragma once
#include "Button.h"
enum class TutorialButtonType
{
	BUTTONTYPE_NONE,
	BUTTONTYPE_SHOWCONTROLS,
	BUTTONTYPE_STARTNEXTLEVEL,
};

class TutorialMenuButton : public Button
{
private:
	TutorialButtonType buttonType;

protected:
	virtual void OnClick() override;

public:
	TutorialMenuButton();
	virtual ~TutorialMenuButton() override;

	void SetButtonType(TutorialButtonType newType) { buttonType = newType; }
};