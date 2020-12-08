#include "pch.h"
#include "TestComponent.h"
#include "Entity.h"
#include "Common.h"

TestComponent::TestComponent()
{

}

void TestComponent::OnUpdate(float deltaTime)
{
	glm::quat currentRot = this->m_entity->GetTransform()->GetGlobalRotationQuaternion();
	glm::quat normed = glm::normalize(currentRot);

	// Rotating 90 degrees around the y axis per second
	glm::quat additionRot = Utility::GetRotationQuaternion(((3.14f * 0.25f) * deltaTime), glm::vec3(0, 1, 0));

	// Calculating resultant rotation (order is important)
	glm::quat result = additionRot * currentRot;

	this->m_entity->GetTransform()->SetGlobalRotationQuaternion(result);
}

void TestComponent::OnRender()
{

}