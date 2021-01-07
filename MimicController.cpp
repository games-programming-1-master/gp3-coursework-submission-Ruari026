#include "MimicController.h"
#include "Utility.h"
#include "Entity.h"

MimicController::MimicController()
{
}

MimicController::~MimicController()
{
}


/*
========================================================================================================================================================================================================
Inherited Entity Methods
========================================================================================================================================================================================================
*/
void MimicController::OnStart()
{
	currentTime = Utility::GetRandomFloat(minTimeBetweenJumps, maxTimeBetweenJumps);

	glm::vec3 mimicPos = m_entity->GetTransform()->GetGlobalPosition();
	theRB->Get();
}

void MimicController::OnUpdate(float deltaTime)
{
	currentTime -= deltaTime;
	if (currentTime <= 0)
	{
		if (theRB != nullptr)
		{
			glm::vec3 mimicPos = m_entity->GetTransform()->GetGlobalPosition();

			btRigidBody* r = theRB->Get();

			theRB->Get()->applyForce(btVector3(0, 150, 0), btVector3(mimicPos.x, mimicPos.y, mimicPos.z));
			theRB->Get()->activate();
		}

		// Resets jump timer
		currentTime = Utility::GetRandomFloat(minTimeBetweenJumps, maxTimeBetweenJumps);
	}
}

void MimicController::OnRender()
{
}