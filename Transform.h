#pragma once
#include"Common.h"
class Transform
{
private:
	Transform* m_parentTransform = nullptr;

	glm::vec3 m_localPosition = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 m_forward = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 m_right = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 m_up = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 m_scale = glm::vec3(1.f, 1.f, 1.f);
	
	glm::quat m_localRotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

	glm::mat4 m_transformMatrix = glm::mat4();

	bool m_isDirty = true;

	glm::mat4 UpdateTransform();

public:
	Transform();
	Transform(glm::vec3 pos);
	Transform(glm::vec3 pos, glm::vec3 rot);
	Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);

	// Position
	inline glm::vec3 GetLocalPosition() 
	{
		// Only returning local position, no transformation required
		return m_localPosition; 
	}
	inline glm::vec3 GetGlobalPosition() 
	{
		// Transformation required if entity has a parent
		if (this->m_parentTransform != nullptr)
		{
			// Parent's position
			glm::vec3 parentPos = m_parentTransform->GetGlobalPosition();

			// Local Position
			glm::vec3 localPos = this->GetLocalPosition();
			return (parentPos + localPos);
		}
		// Otherwise no transformation needed, global position is the same as local position
		else
		{
			return m_localPosition;
		}
	}

	inline void SetLocalPosition(glm::vec3 newPosition)
	{
		m_isDirty = true;

		// No transformation required
		m_localPosition = newPosition;
	}
	inline void SetGlobalPosition(glm::vec3 newPosition)
	{
		m_isDirty = true;

		// Transformation required if entity has a parent
		if (this->m_parentTransform != nullptr)
		{
			m_localPosition = (newPosition - m_parentTransform->GetGlobalPosition());
		}
		// Otherwise no transformation required, global rotation will be the same as local rotation
		else
		{
			m_localPosition = newPosition;
		}
	}

	inline glm::vec3 GetForward() { if (m_isDirty) { UpdateTransform(); }return m_forward; }
	inline glm::vec3 GetRight() { if (m_isDirty) { UpdateTransform(); }return m_right; }
	inline glm::vec3 GetUp() { if (m_isDirty) { UpdateTransform(); }return m_up; }
	
	// Rotation
	inline glm::quat GetLocalRotationQuaternion() 
	{
		// Only getting local rotation, no transformation required
		return m_localRotation;
	}
	inline glm::quat GetGlobalRotationQuaternion() 
	{
		// Transformation required if entity has a parent
		if (this->m_parentTransform != nullptr)
		{
			return (m_localRotation * this->m_parentTransform->GetGlobalRotationQuaternion());
		}
		// Otherwise no transformation needed, global rotation is the same as local rotation
		else
		{
			return m_localRotation;
		}
	}

	inline void SetLocalRotationQuaternion(glm::quat newRotation)
	{
		m_isDirty = true;

		// Just need to convert to euler angles
		m_localRotation = newRotation;
	}
	inline void SetGlobalRotationQuaternion(glm::quat newRotation)
	{
		m_isDirty = true;

		// Transformation required if entity has a parent
		if (this->m_parentTransform != nullptr)
		{
			m_localRotation = newRotation;
		}
		// Otherwise no transformation required, global rotation will be the same as local rotation
		else
		{
			m_localRotation = newRotation;
		}
	}

	// Scale
	inline glm::vec3 GetScale() { return m_scale; }
	inline void SetScale(glm::vec3 newScale) { m_isDirty = true; m_scale = newScale; }

	// Other setters
	inline void SetParentTransform(Transform* newParent) { m_parentTransform = newParent; }
	// Other getters
	inline glm::mat4 GetTransformationMatrix() { if (m_isDirty)return UpdateTransform(); else return m_transformMatrix; }
};