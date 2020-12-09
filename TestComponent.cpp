#include "pch.h"
#include "TestComponent.h"
#include "Entity.h"
#include "Input.h"

TestComponent::TestComponent()
{

}

void TestComponent::OnUpdate(float deltaTime)
{
	glm::quat currentRot = this->m_entity->GetTransform()->GetGlobalRotationQuaternion();
	glm::quat additionRot = Utility::GetRotationQuaternion(rotationSpeed * deltaTime, rotationDirection);

	this->m_entity->GetTransform()->SetGlobalRotationQuaternion(additionRot * currentRot);
}

void TestComponent::OnRender()
{

}