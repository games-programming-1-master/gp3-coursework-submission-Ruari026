#include "Directions.h"

Directions DirectionsUtility::ConvertVectorToDirection(glm::ivec2 vector)
{
	if (vector == glm::ivec2(0, 1))
	{
		return Directions::UP;
	}
	else if (vector == glm::ivec2(1, 0))
	{
		return Directions::RIGHT;
	}
	else if (vector == glm::ivec2(0, -1))
	{
		return Directions::DOWN;
	}
	else if (vector == glm::ivec2(-1, 0))
	{
		return Directions::LEFT;
	}
}

glm::ivec2 DirectionsUtility::ConvertDirectionToVector(Directions direction)
{
	switch (direction)
	{
	case (Directions::UP):
		return glm::ivec2(0, 1);
		break;

	case (Directions::RIGHT):
		return glm::ivec2(1, 0);
		break;

	case (Directions::DOWN):
		return glm::ivec2(0, -1);
		break;

	case (Directions::LEFT):
		return glm::ivec2(-1, 0);
		break;
	}
}

Directions DirectionsUtility::GetOppositeDirection(Directions d)
{
	switch (d)
	{
	case (Directions::UP):
		return Directions::DOWN;
		break;

	case (Directions::RIGHT):
		return Directions::LEFT;
		break;

	case (Directions::DOWN):
		return Directions::UP;
		break;

	case (Directions::LEFT):
		return Directions::RIGHT;
		break;
	}
}