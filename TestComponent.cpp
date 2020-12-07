#include "pch.h"
#include "TestComponent.h"
#include "Entity.h"
#include "Common.h"

TestComponent::TestComponent()
{

}

void TestComponent::OnUpdate(float deltaTime)
{
	//glm::vec3 currentRot = this->m_entity->GetTransform()->GetGlobalRotationEuler();
	//currentRot += (rotationDirection * rotationSpeed * deltaTime);

	//this->m_entity->GetTransform()->SetGlobalRotationEuler(currentRot);
}

void TestComponent::OnRender()
{

}