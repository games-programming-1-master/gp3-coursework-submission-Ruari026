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
	
	glm::vec3 m_localRotation = glm::vec3(0.0f, 0.0f, 0.0f);

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
			glm::vec3 totalPos = parentPos + localPos;

			// Rotated Local Position
			glm::vec3 eulerRotation = this->GetGlobalRotationEuler();

			glm::vec3 eulerRotationX = glm::vec3(eulerRotation.x, 0.0f, 0.0f);
			glm::vec3 eulerRotationY = glm::vec3(0.0f, eulerRotation.y, 0.0f);
			glm::vec3 eulerRotationZ = glm::vec3(0.0f, 0.0f, eulerRotation.z);

			// Getting rotation as a quaternion for transformation
			glm::quat quaternionX = glm::quat();
			quaternionX.x = (sin(eulerRotationX.x / 2) * cos(eulerRotationX.y / 2) * cos(eulerRotationX.z / 2)) + (cos(eulerRotationX.x / 2) * sin(eulerRotationX.y / 2) * sin(eulerRotationX.z / 2));
			quaternionX.y = (cos(eulerRotationX.x / 2) * sin(eulerRotationX.y / 2) * cos(eulerRotationX.z / 2)) + (sin(eulerRotationX.x / 2) * cos(eulerRotationX.y / 2) * sin(eulerRotationX.z / 2));
			quaternionX.z = (cos(eulerRotationX.x / 2) * cos(eulerRotationX.y / 2) * sin(eulerRotationX.z / 2)) + (sin(eulerRotationX.x / 2) * sin(eulerRotationX.y / 2) * cos(eulerRotationX.z / 2));
			quaternionX.w = (cos(eulerRotationX.x / 2) * cos(eulerRotationX.y / 2) * cos(eulerRotationX.z / 2)) + (sin(eulerRotationX.x / 2) * sin(eulerRotationX.y / 2) * sin(eulerRotationX.z / 2));
			glm::quat quaternionY = glm::quat();
			quaternionY.x = (sin(eulerRotationY.x / 2) * cos(eulerRotationY.y / 2) * cos(eulerRotationY.z / 2)) + (cos(eulerRotationY.x / 2) * sin(eulerRotationY.y / 2) * sin(eulerRotationY.z / 2));
			quaternionY.y = (cos(eulerRotationY.x / 2) * sin(eulerRotationY.y / 2) * cos(eulerRotationY.z / 2)) + (sin(eulerRotationY.x / 2) * cos(eulerRotationY.y / 2) * sin(eulerRotationY.z / 2));
			quaternionY.z = (cos(eulerRotationY.x / 2) * cos(eulerRotationY.y / 2) * sin(eulerRotationY.z / 2)) + (sin(eulerRotationY.x / 2) * sin(eulerRotationY.y / 2) * cos(eulerRotationY.z / 2));
			quaternionY.w = (cos(eulerRotationY.x / 2) * cos(eulerRotationY.y / 2) * cos(eulerRotationY.z / 2)) + (sin(eulerRotationY.x / 2) * sin(eulerRotationY.y / 2) * sin(eulerRotationY.z / 2));
			glm::quat quaternionZ = glm::quat();
			quaternionZ.x = (sin(eulerRotationZ.x / 2) * cos(eulerRotationZ.y / 2) * cos(eulerRotationZ.z / 2)) + (cos(eulerRotationZ.x / 2) * sin(eulerRotationZ.y / 2) * sin(eulerRotationZ.z / 2));
			quaternionZ.y = (cos(eulerRotationZ.x / 2) * sin(eulerRotationZ.y / 2) * cos(eulerRotationZ.z / 2)) + (sin(eulerRotationZ.x / 2) * cos(eulerRotationZ.y / 2) * sin(eulerRotationZ.z / 2));
			quaternionZ.z = (cos(eulerRotationZ.x / 2) * cos(eulerRotationZ.y / 2) * sin(eulerRotationZ.z / 2)) + (sin(eulerRotationZ.x / 2) * sin(eulerRotationZ.y / 2) * cos(eulerRotationZ.z / 2));
			quaternionZ.w = (cos(eulerRotationZ.x / 2) * cos(eulerRotationZ.y / 2) * cos(eulerRotationZ.z / 2)) + (sin(eulerRotationZ.x / 2) * sin(eulerRotationZ.y / 2) * sin(eulerRotationZ.z / 2));

			glm::vec3 rotatedPos = (quaternionX * quaternionZ * quaternionY * totalPos);
			return rotatedPos;
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
	inline glm::vec3 GetLocalRotationEuler() 
	{
		// Only returning local euler rotation, no transformation required
		return m_localRotation; 
	}
	inline glm::quat GetLocalRotationQuaternion() 
	{
		// Need to transform to quaternion
		return Transform::ConvertEulerToQuaternion(m_localPosition);
	}

	inline glm::vec3 GetGlobalRotationEuler() 
	{ 
		// Transformation required if entity has a parent
		if (this->m_parentTransform != nullptr)
		{
			return (m_localRotation + m_parentTransform->GetGlobalRotationEuler());
		}
		// Otherwise no transformation needed, global rotation is the same as local rotation
		else
		{
			return m_localRotation;
		}
	}
	inline glm::quat GetGlobalRotationQuaternion() 
	{
		// Transformation required if entity has a parent
		if (this->m_parentTransform != nullptr)
		{
			return Transform::ConvertEulerToQuaternion(m_localRotation + m_parentTransform->GetGlobalRotationEuler());
		}
		// Otherwise no transformation needed, global rotation is the same as local rotation
		else
		{
			return Transform::ConvertEulerToQuaternion(m_localRotation);
		}
	}

	inline void SetLocalRotationEuler(glm::vec3 newRotation) 
	{ 
		m_isDirty = true;

		// No transformation needed
		m_localRotation = newRotation;
	}
	inline void SetLocalRotationQuaternion(glm::quat newRotation)
	{
		m_isDirty = true;

		// Just need to convert to euler angles
		m_localRotation = Transform::ConvertQuaternionToEuler(newRotation);
	}

	inline void SetGlobalRotationEuler(glm::vec3 newRotation) 
	{
		m_isDirty = true;

		// Transformation required if entity has a parent
		if (this->m_parentTransform != nullptr)
		{
			m_localRotation = (newRotation - m_parentTransform->GetGlobalRotationEuler());
		}
		// Otherwise no transformation required, global rotation will be the same as local rotation
		else
		{
			m_localRotation = newRotation;
		}
	}
	inline void SetGlobalRotationQuaternion(glm::quat newRotation)
	{
		m_isDirty = true;

		// Transformation required if entity has a parent
		if (this->m_parentTransform != nullptr)
		{
			m_localRotation = (Transform::ConvertQuaternionToEuler(newRotation) - m_parentTransform->GetGlobalRotationEuler());
		}
		// Otherwise no transformation required, global rotation will be the same as local rotation
		else
		{
			m_localRotation = Transform::ConvertQuaternionToEuler(newRotation);
		}
	}

	// Scale
	inline glm::vec3 GetScale() { return m_scale; }
	inline void SetScale(glm::vec3 newScale) { m_isDirty = true; m_scale = newScale; }

	// Other setters
	inline void SetParentTransform(Transform* newParent) { m_parentTransform = newParent; }
	// Other getters
	inline glm::mat4 GetTransformationMatrix() { if (m_isDirty)return UpdateTransform(); else return m_transformMatrix; }

	// Utility
	inline static glm::vec3 ConvertQuaternionToEuler(glm::quat quaternion)
	{
		glm::vec3 newEulerAngles = glm::vec3();

		// Heading
		newEulerAngles.x = atan2(((2 * quaternion.x * quaternion.w) - (2 * quaternion.y * quaternion.z)), ((1) - (2 * quaternion.x * quaternion.x) - (2 * quaternion.z * quaternion.z)));
		// Attitude
		newEulerAngles.y = asin((2 * quaternion.x * quaternion.y) + (2 * quaternion.z * quaternion.w));
		// Bank
		newEulerAngles.z = atan2(((2 * quaternion.y * quaternion.w) - (2 * quaternion.x * quaternion.z)), ((1) - (2 * quaternion.y * quaternion.y) - (2 * quaternion.z * quaternion.z)));

		return newEulerAngles;
	}
	inline static glm::quat ConvertEulerToQuaternion(glm::vec3 eulerAngles)
	{
		glm::quat newQuaternion = glm::quat();
		newQuaternion.x = (sin(eulerAngles.x / 2) * cos(eulerAngles.y / 2) * cos(eulerAngles.z / 2)) + (cos(eulerAngles.x / 2) * sin(eulerAngles.y / 2) * sin(eulerAngles.z / 2));
		newQuaternion.y = (cos(eulerAngles.x / 2) * sin(eulerAngles.y / 2) * cos(eulerAngles.z / 2)) + (sin(eulerAngles.x / 2) * cos(eulerAngles.y / 2) * sin(eulerAngles.z / 2));
		newQuaternion.z = (cos(eulerAngles.x / 2) * cos(eulerAngles.y / 2) * sin(eulerAngles.z / 2)) + (sin(eulerAngles.x / 2) * sin(eulerAngles.y / 2) * cos(eulerAngles.z / 2));
		newQuaternion.w = (cos(eulerAngles.x / 2) * cos(eulerAngles.y / 2) * cos(eulerAngles.z / 2)) + (sin(eulerAngles.x / 2) * sin(eulerAngles.y / 2) * sin(eulerAngles.z / 2));

		return newQuaternion;
	}
};