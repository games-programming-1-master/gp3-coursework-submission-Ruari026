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

	void SetHeldKey(SDL_Keycode key, bool state);
	void SetUpKey(SDL_Keycode key);
	void SetDownKey(SDL_Keycode key);

	bool GetKey(SDL_Keycode key); //check if it's currently held down or not
	bool GetKeyDown(SDL_Keycode key); //check if the key was pressed down this frame
	bool GetKeyUp(SDL_Keycode key); //check if the key was pressed up this frame

	void ResetUpDownKeys() { m_state.ResetInput(); }

	glm::ivec2 GetMousePos() { return m_state.mousePos; }
	glm::ivec2 GetMouseMovement() { return m_state.mouseMovement; }
	
	void MoveMouse(glm::ivec2 delta);
	void LockAndHideCursor(SDL_bool lockAndHide);

	void SetMouseDown(SDL_MouseButtonEvent event);
	void SetMouseUp(SDL_MouseButtonEvent event);

	bool GetMouseDown(Uint8 mouseButton) { return m_state.mouseDown[mouseButton]; }
	bool GetMouseUp(Uint8 mouseButton) { return m_state.mouseUp[mouseButton]; }
	bool GetMouseHeld(Uint8 mouseButton) { return m_state.mouseHeld[mouseButton]; }
};