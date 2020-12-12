#include "Room_1Door_Normal.h"
#include "RoomPrefab_1Door.h"

// General Engine Includes
#include "Resources.h"
// Required Components
#include "MeshRenderer.h"
#include "RigidBody.h"
// Required Colliders
#include "BoxShape.h"

Room_1Door_Normal::Room_1Door_Normal(std::string name) : Entity(name)
{
	// Parent Prefab to build off from
	Entity* parentPrefab = new RoomPrefab_1Door("1Door_Base");
	this->AddChild(parentPrefab);

	// Adding Corner Pillars
	{
		// Front Right Pillar
		{
			Entity* frontRightPillar = new Entity("Corner Pillar 1");
			this->AddChild(frontRightPillar);
			frontRightPillar->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Pillar (Corner).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
			);
			MeshRenderer* m = frontRightPillar->GetComponent<MeshRenderer>();
			frontRightPillar->GetTransform()->SetGlobalPosition(glm::vec3(8.5f, 3.0f, -8.5f));
			frontRightPillar->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			frontRightPillar->AddComponent<RigidBody>();
			frontRightPillar->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 0.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			frontRightPillar->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Back Right Pillar
		{
			Entity* backRightPillar = new Entity("Corner Pillar 2");
			this->AddChild(backRightPillar);
			backRightPillar->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Pillar (Corner).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
			);
			MeshRenderer* m = backRightPillar->GetComponent<MeshRenderer>();
			backRightPillar->GetTransform()->SetGlobalPosition(glm::vec3(8.5f, 3.0f, 8.5f));
			backRightPillar->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)));
			backRightPillar->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			backRightPillar->AddComponent<RigidBody>();
			backRightPillar->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 0.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			backRightPillar->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Back Left Pillar
		{
			Entity* backLeftPillar = new Entity("Corner Pillar 3");
			this->AddChild(backLeftPillar);
			backLeftPillar->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Pillar (Corner).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
			);
			MeshRenderer* m = backLeftPillar->GetComponent<MeshRenderer>();
			backLeftPillar->GetTransform()->SetGlobalPosition(glm::vec3(-8.5f, 3.0f, 8.5f));
			backLeftPillar->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
			backLeftPillar->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			backLeftPillar->AddComponent<RigidBody>();
			backLeftPillar->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 0.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			backLeftPillar->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Front Left Pillar
		{
			Entity* frontLeftPillar = new Entity("Corner Pillar 4");
			this->AddChild(frontLeftPillar);
			frontLeftPillar->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Pillar (Corner).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
			);
			MeshRenderer* m = frontLeftPillar->GetComponent<MeshRenderer>();
			frontLeftPillar->GetTransform()->SetGlobalPosition(glm::vec3(-8.5f, 3.0f, -8.5f));
			frontLeftPillar->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((3.14f * 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)));
			frontLeftPillar->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			frontLeftPillar->AddComponent<RigidBody>();
			frontLeftPillar->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 0.5f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			frontLeftPillar->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}
	}

	// Adding Side Pillars
	{
		// Back Door Pillar 1
		{
			Entity* doorPillar1 = new Entity("Door Pillar 1");
			this->AddChild(doorPillar1);
			doorPillar1->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Pillar (Half).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
			);
			MeshRenderer* m = doorPillar1->GetComponent<MeshRenderer>();
			doorPillar1->GetTransform()->SetGlobalPosition(glm::vec3(-2.0f, 3.0f, 8.5f));
			doorPillar1->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 0.5f), glm::vec3(0, 1, 0)));
			doorPillar1->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			doorPillar1->AddComponent<RigidBody>();
			doorPillar1->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 1.0f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			doorPillar1->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}

		// Back Door Pillar 2
		{
			Entity* doorPillar2 = new Entity("Door Pillar 2");
			this->AddChild(doorPillar2);
			doorPillar2->AddComponent(
				new MeshRenderer(
					Resources::GetInstance()->GetModel("Models/Pillar (Half).obj"),
					Resources::GetInstance()->GetShader("simple"),
					Resources::GetInstance()->GetTexture("Images/Textures/Brick (Simple).png"))
			);
			MeshRenderer* m = doorPillar2->GetComponent<MeshRenderer>();
			doorPillar2->GetTransform()->SetGlobalPosition(glm::vec3(2.0f, 3.0f, 8.5f));
			doorPillar2->GetTransform()->SetGlobalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 0.5f), glm::vec3(0, 1, 0)));
			doorPillar2->GetTransform()->SetScale(glm::vec3(1.f, 1.f, 1.f));

			doorPillar2->AddComponent<RigidBody>();
			doorPillar2->GetComponent<RigidBody>()->Init(new BoxShape(glm::vec3(0.5f, 3.0f, 1.0f)), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			doorPillar2->GetComponent<RigidBody>()->Get()->setMassProps(0, btVector3());
		}
	}
}