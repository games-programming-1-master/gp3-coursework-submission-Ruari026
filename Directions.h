#pragma once
#include "pch.h"
#include "Common.h"

enum class Directions
{
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3
};


class DirectionsUtility
{
public:
	static Directions ConvertVectorToDirection(glm::ivec2 vector);
	static glm::ivec2 ConvertDirectionToVector(Directions direction);
	static Directions GetOppositeDirection(Directions d);
};