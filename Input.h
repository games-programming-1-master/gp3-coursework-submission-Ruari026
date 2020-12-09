#pragma once
#include "Common.h"
#include "InputState.h"
#define INPUT Input::GetInstance()

class Input
{
private:
	Input();
	static Input* m_instance;
	InputState m_state;

public:
	static Input* GetInstance();
	void SetKey(SDL_Keycode key, bool state);
	bool GetKey(SDL_Keycode key); //check if it's currently down or not

	glm::ivec2 GetMousePos() { return m_state.mousePos; }
	glm::ivec2 GetMouseMovement() { return m_state.mouseMovement; }
	void MoveMouse(glm::ivec2 delta) 
	{ 
		m_state.mousePos += delta; 
		m_state.mouseMovement = delta; 
	}
};

