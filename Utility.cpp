#include "Utility.h"

glm::quat Utility::GetRotationQuaternion(float angle, glm::vec3 rotationAxis)
{
	float w = std::cos(angle / 2);

	float x = std::sin(angle / 2) * rotationAxis.x;
	float y = std::sin(angle / 2) * rotationAxis.y;
	float z = std::sin(angle / 2) * rotationAxis.z;

	return glm::quat(w, x, y, z);
}

float Utility::Lerp(float min, float max, float time)
{
	if (time < 0)
		time = 0;
	else if (time > 1)
		time = 1;

	return (min + time * (max - min));
}