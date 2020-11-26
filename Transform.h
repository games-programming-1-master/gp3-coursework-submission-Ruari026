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

	inline void SetPosition(glm::vec3 newPos) { m_isDirty = true; m_localPosition = newPos; }

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
		// Transforming euler angles into quaternion representation
		glm::vec3 eulerAngles = GetLocalRotationEuler();

		glm::quat quaternion = glm::quat();
		quaternion.x = (sin(eulerAngles.x / 2) * cos(eulerAngles.y / 2) * cos(eulerAngles.z / 2)) + (cos(eulerAngles.x / 2) * sin(eulerAngles.y / 2) * sin(eulerAngles.z / 2));
		quaternion.y = (cos(eulerAngles.x / 2) * sin(eulerAngles.y / 2) * cos(eulerAngles.z / 2)) + (sin(eulerAngles.x / 2) * cos(eulerAngles.y / 2) * sin(eulerAngles.z / 2));
		quaternion.z = (cos(eulerAngles.x / 2) * cos(eulerAngles.y / 2) * sin(eulerAngles.z / 2)) + (sin(eulerAngles.x / 2) * sin(eulerAngles.y / 2) * cos(eulerAngles.z / 2));
		quaternion.w = (cos(eulerAngles.x / 2) * cos(eulerAngles.y / 2) * cos(eulerAngles.z / 2)) + (sin(eulerAngles.x / 2) * sin(eulerAngles.y / 2) * sin(eulerAngles.z / 2));

		return quaternion;
	}

	inline glm::vec3 GetGlobalRotationEuler() 
	{ 
		// Transformation required if entity has a parent
		if (this->m_parentTransform != nullptr)
		{
			return (this->GetLocalRotationEuler() + this->m_parentTransform->GetGlobalRotationEuler());
		}
		// Otherwise no transformation needed, global rotation is the same as local rotation
		else
		{
			return m_localRotation;
		}
	}
	inline glm::quat GetGlobalRotationQuaternion() 
	{
		// Transforming euler angles into quaternion representation
		glm::vec3 eulerAngles = GetGlobalRotationEuler();

		glm::quat quaternion = glm::quat();
		quaternion.x = (sin(eulerAngles.x / 2) * cos(eulerAngles.y / 2) * cos(eulerAngles.z / 2)) + (cos(eulerAngles.x / 2) * sin(eulerAngles.y / 2) * sin(eulerAngles.z / 2));
		quaternion.y = (cos(eulerAngles.x / 2) * sin(eulerAngles.y / 2) * cos(eulerAngles.z / 2)) + (sin(eulerAngles.x / 2) * cos(eulerAngles.y / 2) * sin(eulerAngles.z / 2));
		quaternion.z = (cos(eulerAngles.x / 2) * cos(eulerAngles.y / 2) * sin(eulerAngles.z / 2)) + (sin(eulerAngles.x / 2) * sin(eulerAngles.y / 2) * cos(eulerAngles.z / 2));
		quaternion.w = (cos(eulerAngles.x / 2) * cos(eulerAngles.y / 2) * cos(eulerAngles.z / 2)) + (sin(eulerAngles.x / 2) * sin(eulerAngles.y / 2) * sin(eulerAngles.z / 2));

		return quaternion;
	}

	inline void SetLocalRotationEuler(glm::vec3 newRotation) 
	{ 
		m_isDirty = true; 

		// No transformation required, directly setting local position
		m_localRotation = newRotation; 
	}
	inline void SetLocalRotationQuaternion(glm::quat newRotation)
	{
		glm::vec3 newEuler = glm::vec3();

		// Heading
		newEuler.x = atan2(((2 * newRotation.y * newRotation.w) - (2 * newRotation.x * newRotation.z)), ((1) - (2 * newRotation.y * newRotation.y) - (2 * newRotation.z * newRotation.z)));
		// Attitude
		newEuler.y = asin((2 * newRotation.x * newRotation.y) + (2 * newRotation.z * newRotation.w));
		// Bank
		newEuler.z = atan2(((2 * newRotation.x * newRotation.w) - (2 * newRotation.y * newRotation.z)), ((1) - (2 * newRotation.x * newRotation.x) - (2 * newRotation.z * newRotation.z)));

		this->m_localRotation = newEuler;
	}

	inline void SetGlobalRotationEuler(glm::vec3 newRotation) 
	{
		m_isDirty = true;

		// Transformation required if entity has a parent
		if (this->m_parentTransform != nullptr)
		{
			m_localRotation = (newRotation - this->GetGlobalRotationEuler());
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

	//getters
	inline glm::mat4 GetTransformationMatrix() { if (m_isDirty)return UpdateTransform(); else return m_transformMatrix; }
};

