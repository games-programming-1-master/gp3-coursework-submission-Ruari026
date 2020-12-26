#include "pch.h"
#include "Button.h"
#include "Entity.h"
#include "Input.h"

Button::Button()
{
}
Button::~Button()
{
}


void Button::OnStart()
{
}

void Button::OnUpdate(float deltaTime)
{
	switch (currentState)
	{
		case (ButtonState::BUTTONSTATE_ACTIVE):
		{
			// Checking if the mouse is over the button
			if (IsMouseWithinImageRect())
			{
				// If it is change to hovered state
				ChangeState(ButtonState::BUTTONSTATE_HOVERED);
			}
		}
		break;

		case (ButtonState::BUTTONSTATE_PRESSED):
		{
			// Checking for left mouse click up
			if (Input::GetInstance()->GetMouseUp(SDL_BUTTON_LEFT))
			{
				// Only runs button behaviour if click was still within button rect
				if (IsMouseWithinImageRect())
				{
					ChangeState(ButtonState::BUTTONSTATE_HOVERED);
				}
				else
				{
					ChangeState(ButtonState::BUTTONSTATE_ACTIVE);
				}
			}
		}
		break;

		case (ButtonState::BUTTONSTATE_DISABLED):
		{
			// No Special Behaviour
		}
		break;

		case (ButtonState::BUTTONSTATE_HOVERED):
		{
			// Checking for left mouse click down
			if (Input::GetInstance()->GetMouseDown(SDL_BUTTON_LEFT))
			{
				ChangeState(ButtonState::BUTTONSTATE_PRESSED);
			}

			// Otherwise checking for mouse leaving button rect
			if (!IsMouseWithinImageRect())
			{
				ChangeState(ButtonState::BUTTONSTATE_ACTIVE);
			}
		}
		break;
	}
}

void Button::OnRender()
{
}

void Button::ChangeState(ButtonState newState)
{
	currentState = newState;

	if (buttonRenderer == nullptr)
	{
		return;
	}
	else
	{
		switch (currentState)
		{
		case (ButtonState::BUTTONSTATE_ACTIVE):
		{
			// Update renderer color
			buttonRenderer->SetImageColor(activeColor);
		}
		break;

		case (ButtonState::BUTTONSTATE_HOVERED):
		{
			// Update renderer color
			buttonRenderer->SetImageColor(hoveredColor);
		}
		break;

		case (ButtonState::BUTTONSTATE_PRESSED):
		{
			// Update renderer color
			buttonRenderer->SetImageColor(pressedColor);
		}
		break;

		case (ButtonState::BUTTONSTATE_DISABLED):
		{
			// Update renderer color
			buttonRenderer->SetImageColor(disabledColor);
		}
		break;
		}
	}
}

bool Button::IsMouseWithinImageRect()
{
	// Can't check if mouse is within rect if renderer hasn't been set
	if (buttonRenderer == nullptr)
		return false;

	// Getting mouse position in screen space (top left = (0, 0))
	glm::ivec2 mousePos = glm::ivec2(0, 0);
	SDL_GetMouseState(&mousePos.x, &mousePos.y);

	// Checking if mouse is inside button rect (based on renderer width & height)
	glm::vec3 buttonPosition = m_entity->GetTransform()->GetGlobalPosition();
	glm::vec2 buttonSize = buttonRenderer->GetImageSize();
	// Checking x axis
	if (mousePos.x > buttonPosition.x && mousePos.x < (buttonPosition.x + buttonSize.x))
	{
		// checking y axis
		if (mousePos.y < buttonPosition.y && mousePos.y >(buttonPosition.y - buttonSize.y))
		{
			return true;
		}
	}

	// Otherwise mouse is outside rect
	return false;
}