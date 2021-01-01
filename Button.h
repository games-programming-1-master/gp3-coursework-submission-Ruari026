#pragma once
#include "Component.h"
#include "ImageRenderer.h"
#include "TextRenderer.h"

enum class ButtonState
{
	BUTTONSTATE_ACTIVE,
	BUTTONSTATE_HOVERED,
	BUTTONSTATE_PRESSED,
	BUTTONSTATE_DISABLED
};

class Button : public Component
{
private:
	ImageRenderer* buttonRenderer = nullptr;

	ButtonState currentState = ButtonState::BUTTONSTATE_ACTIVE;

	glm::vec4 activeColor = glm::vec4(0.88f, 0.88f, 0.88f, 1.0f);
	glm::vec4 hoveredColor = glm::vec4(0.77f, 0.77f, 0.77f, 1.0f);
	glm::vec4 pressedColor = glm::vec4(1.0f, 0.9f, 0.85f, 1.0f);
	glm::vec4 disabledColor = glm::vec4(0.55f, 0.55f, 0.55f, 1.0f);

	bool IsMouseWithinImageRect();

protected:
	virtual void OnClick() {};

public:
	Button();
	virtual ~Button() override;

	virtual void OnStart() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	void SetButtonRenderer(ImageRenderer* theRenderer) { buttonRenderer = theRenderer; }

	void ChangeState(ButtonState newState);
};