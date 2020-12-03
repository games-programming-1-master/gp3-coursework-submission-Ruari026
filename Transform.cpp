#include "pch.h"
#include "Transform.h"

glm::mat4 Transform::UpdateTransform()
{
	m_transformMatrix = glm::translate(glm::mat4(1.f), GetGlobalPosition());
	glm::mat4 currentRotate = glm::mat4_cast(GetGlobalRotationQuaternion());
	m_transformMatrix = m_transformMatrix * currentRotate;
	m_transformMatrix = scale(m_transformMatrix, m_scale);

	m_forward = glm::normalize(glm::rotate(GetGlobalRotationQuaternion(), glm::vec3(0, 0, -1)));
	m_up = glm::normalize(glm::rotate(GetGlobalRotationQuaternion(), glm::vec3(0, 1, 0)));
	m_right = glm::normalize(glm::rotate(GetGlobalRotationQuaternion(), glm::vec3(1, 0, 0)));

	m_isDirty = false;
	return m_transformMatrix;
}

Transform::Transform()
{
}

Transform::Transform(glm::vec3 pos) : Transform()
{
	m_localPosition = pos;
}

Transform::Transform(glm::vec3 pos, glm::vec3 rot) : Transform(pos)
{
	m_localRotation = rot;
}

Transform::Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) : Transform(pos, rot)
{
	m_scale = scale;
}