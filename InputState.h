#pragma once
#include "pch.h"
#include "Common.h"

struct InputState
{
	InputState()
	{
		mouseHeld.fill(false);
		heldKeys.fill(false);
	}

	// Key Input
	std::array<char, 400> heldKeys;
	std::array<char, 400> downKeys;
	std::array<char, 400> upKeys;

	// Cursor Movement
	glm::ivec2 mousePos;
	glm::ivec2 mouseMovement;

	// Mouse Input
	std::array<Uint8, 5> mouseDown;
	std::array<Uint8, 5> mouseUp;
	std::array<Uint8, 5> mouseHeld;

	void ResetInput()
	{
		downKeys.fill(false);
		upKeys.fill(false);
		
		mouseDown.fill(false);
		mouseUp.fill(false);
	}
};