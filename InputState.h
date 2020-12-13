#pragma once
#include "pch.h"
#include "Common.h"

struct InputState
{
	InputState()
	{
		heldKeys.fill(false);
	}

	std::array<char, 400> heldKeys;

	std::array<char, 400> downKeys;
	std::array<char, 400> upKeys;

	glm::ivec2 mousePos;
	glm::ivec2 mouseMovement;

	void ResetInput()
	{
		downKeys.fill(false);
		upKeys.fill(false);
	}
};