#include "Utility.h"

glm::quat Utility::GetRotationQuaternion(float angle, glm::vec3 rotationAxis)
{
	float w = std::cos(angle / 2);

	float x = std::sin(angle / 2) * rotationAxis.x;
	float y = std::sin(angle / 2) * rotationAxis.y;
	float z = std::sin(angle / 2) * rotationAxis.z;

	return glm::quat(w, x, y, z);
}

float Utility::LerpFloat(float min, float max, float time)
{
	if (time < 0)
		time = 0;
	else if (time > 1)
		time = 1;

	return (min + time * (max - min));
}

glm::vec3 Utility::LerpVec3(glm::vec3 min, glm::vec3 max, float time)
{
	if (time < 0)
		time = 0;
	else if (time > 1)
		time = 1;

	glm::vec3 result = glm::vec3(0, 0, 0);

	result.x = Utility::LerpFloat(min.x, max.x, time);
	result.y = Utility::LerpFloat(min.y, max.y, time);
	result.z = Utility::LerpFloat(min.z, max.z, time);

	return result;
}

std::string Utility::EnumToString(RoomTypes roomType)
{
	switch (roomType)
	{
		case (RoomTypes::ROOMTYPE_ENTRANCE):
		{
			return "ROOMTYPE_ENTRANCE";
		}
		break;

		case (RoomTypes::ROOMTYPE_EXIT):
		{
			return "ROOMTYPE_EXIT";
		}
		break;

		case (RoomTypes::ROOMTYPE_NORMAL):
		{
			return "ROOMTYPE_NORMAL";
		}
		break;

		case (RoomTypes::ROOMTYPE_TOPFLOOR):
		{
			return "ROOMTYPE_TOPFLOOR";
		}
		break;
	}
}