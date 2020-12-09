#pragma once
#include <gtx/quaternion.hpp>
#include <math.h>

class Utility
{
public:
	static glm::quat GetRotationQuaternion(float angle, glm::vec3 rotationAxis);
	static float Lerp(float min, float max, float time);
};