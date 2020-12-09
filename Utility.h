#pragma once
#include <gtx/quaternion.hpp>
#include <math.h>

class Utility
{
public:
	static glm::quat GetRotationQuaternion(float angle, glm::vec3 rotationAxis);
	static float LerpFloat(float min, float max, float time);
	static glm::vec3 LerpVec3(glm::vec3 min, glm::vec3 max, float time);
};