#include "pch.h"
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