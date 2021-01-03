#pragma once
#include "pch.h"

#include "RoomTypes.h"

#include <gtx/quaternion.hpp>
#include <math.h>
#include <random>

class Utility
{
public:
	static glm::quat GetRotationQuaternion(float angle, glm::vec3 rotationAxis);
	static float LerpFloat(float min, float max, float time);
	static glm::vec3 LerpVec3(glm::vec3 min, glm::vec3 max, float time);
	
	static float GetRandomFloat(float min, float max)
	{
		std::random_device device;
		std::mt19937 engine{ device() };
		std::uniform_real_distribution<float> dist(min, max);

		return dist(engine);
	}

	template<class T>
	static T GetRandomFromVector(std::vector<T> vector)
	{
		std::random_device device;
		std::mt19937 engine{ device() };
		std::uniform_int_distribution<int> dist(0, vector.size() - 1);

		return vector[dist(engine)];
	}

	template<class T>
	static bool VectorContains(T elementToCheck, std::vector<T> vector)
	{
		for (auto v : vector)
		{
			if (v == elementToCheck)
			{
				return true;
			}
		}

		return false;
	}

	static std::string EnumToString(RoomTypes roomType);
};