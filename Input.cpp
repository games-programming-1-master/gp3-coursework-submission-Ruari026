#include "pch.h"
#include "Application.h"
#include "Input.h"

Input* Input::m_instance = nullptr;

Input::Input()
{
}

Input* Input::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new Input();
	}

	return m_instance;
}


/*
========================================================================================================================================================================================================
Input Setting
========================================================================================================================================================================================================
*/
void Input::SetHeldKey(SDL_Keycode key, bool state)
{
	int index = key;
	if (key >= SDLK_CAPSLOCK)
	{
		index = (key - SDLK_SCANCODE_MASK) + 128;
	}

	if (index < m_state.heldKeys.size())
	{
		m_state.heldKeys[index] = state;
	}
}

void Input::SetUpKey(SDL_Keycode key)
{
	int index = key;
	if (key >= SDLK_CAPSLOCK)
	{
		index = (key - SDLK_SCANCODE_MASK) + 128;
	}

	if (index < m_state.upKeys.size())
	{
		m_state.upKeys[index] = true;
	}
}

void Input::SetDownKey(SDL_Keycode key)
{
	int index = key;
	if (key >= SDLK_CAPSLOCK)
	{
		index = (key - SDLK_SCANCODE_MASK) + 128;
	}

	if (index < m_state.downKeys.size())
	{
		m_state.downKeys[index] = true;
	}
}

void Input::SetMouseDown(SDL_MouseButtonEvent event)
{
	int index = event.button;
	if (index <= SDL_BUTTON_X2)
	{
		m_state.mouseDown[index] = true;
		m_state.mouseHeld[index] = true;
	}
}

void Input::SetMouseUp(SDL_MouseButtonEvent event)
{
	int index = event.button;
	if (index <= SDL_BUTTON_X2)
	{
		m_state.mouseUp[index] = true;
		m_state.mouseHeld[index] = false;
	}
}

/*
========================================================================================================================================================================================================
Input Checking
========================================================================================================================================================================================================
*/
bool Input::GetKey(SDL_Keycode key)
{
	int index = key;
	if (key >= SDLK_CAPSLOCK)
	{
		index = (key - SDLK_SCANCODE_MASK) + 128;
	}

	if (index < m_state.heldKeys.size())
	{
		return m_state.heldKeys[index];
	}
	else return false;
}

bool Input::GetKeyUp(SDL_Keycode key)
{
	int index = key;
	if (key >= SDLK_CAPSLOCK)
	{
		index = (key - SDLK_SCANCODE_MASK) + 128;
	}

	if (index < m_state.upKeys.size())
	{
		return m_state.upKeys[index];
	}
	else return false;
}

bool Input::GetKeyDown(SDL_Keycode key)
{
	int index = key;
	if (key >= SDLK_CAPSLOCK)
	{
		index = (key - SDLK_SCANCODE_MASK) + 128;
	}

	if (index < m_state.downKeys.size())
	{
		return m_state.downKeys[index];
	}
	else return false;
}


/*
========================================================================================================================================================================================================
Cursor Handling
========================================================================================================================================================================================================
*/
void Input::MoveMouse(glm::ivec2 delta)
{
	if (!SDL_GetRelativeMouseMode())
	{
		// Mouse position has no meaning if sdl has the mouse hidden and locked
		m_state.mousePos += delta;
	}
	m_state.mouseMovement = delta;
}

void Input::LockAndHideCursor(SDL_bool lockAndHide)
{
	// No point changing cursor mode if the request is the same as the current state
	if (SDL_GetRelativeMouseMode() != lockAndHide)
	{
		m_state.mousePos = glm::vec2((WINDOW_W / 2), (WINDOW_H / 2));
		SDL_SetRelativeMouseMode(lockAndHide);
	}
}