#pragma once
#include"Common.h"
class Transform
{
private:
	Transform* m_parentTransform = nullptr;
	std::vector<Transform*> m_childrenTransform;

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

			// Taking rotation into account
			glm::quat rotation = m_parentTransform->GetGlobalRotationQuaternion();
			glm::vec3 rotatedPos = rotation * localPos;

			return (parentPos + rotatedPos);
		}
		// Otherwise no transformation needed, global position is the same as local position
		else
		{
			return m_localPosition;
		}
	}

	inline void SetLocalPosition(glm::vec3 newPosition)
	{
		SetDirty();

		// No transformation required
		m_localPosition = newPosition;
	}
	inline void SetGlobalPosition(glm::vec3 newPosition)
	{
		SetDirty();

		// Transformation required if entity has a parent
		if (this->m_parentTransform != nullptr)
		{
			// Gets parents global position and rotation
			glm::vec3 parentPos = this->m_parentTransform->GetGlobalPosition();
			glm::quat parentRot = this->m_parentTransform->GetGlobalRotationQuaternion();

			glm::vec3 newLocalPos = newPosition - parentPos;
			newLocalPos = glm::inverse(parentRot) * newLocalPos;

			m_localPosition = (newLocalPos);
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
			glm::quat totalRotation = (m_localRotation * this->m_parentTransform->GetGlobalRotationQuaternion());

			return totalRotation;
		}
		// Otherwise no transformation needed, global rotation is the same as local rotation
		else
		{
			return m_localRotation;
		}
	}

	inline void SetLocalRotationQuaternion(glm::quat newRotation)
	{
		SetDirty();

		// Only setting local rotation, no transformation required
		m_localRotation = newRotation;
	}
	inline void SetGlobalRotationQuaternion(glm::quat newRotation)
	{
		SetDirty();

		// Transformation required if entity has a parent
		if (this->m_parentTransform != nullptr)
		{
			glm::quat parentRotation = this->m_parentTransform->GetGlobalRotationQuaternion();
			glm::quat newLocalRotation = glm::inverse(parentRotation) * newRotation;
			
			m_localRotation = newLocalRotation;
		}
		// Otherwise no transformation required, global rotation will be the same as local rotation
		else
		{
			m_localRotation = newRotation;
		}
	}

	// Scale
	inline glm::vec3 GetScale() { return m_scale; }
	inline void SetScale(glm::vec3 newScale) { SetDirty(); m_scale = newScale; }

	// Other setters
	inline void SetParentTransform(Transform* newParent) { m_parentTransform = newParent; }
	inline void AddChildTransform(Transform* newChild) { m_childrenTransform.push_back(newChild); }
	inline void SetDirty() 
	{
		this->m_isDirty = true;

		for (auto& c : m_childrenTransform)
		{
			c->SetDirty();
		}
	}
	// Other getters
	inline glm::mat4 GetTransformationMatrix() { if (m_isDirty)return UpdateTransform(); else return m_transformMatrix; }
};