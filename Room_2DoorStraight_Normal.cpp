#include "Room_2DoorStraight_Normal.h"

#include "RoomPrefab_Straight.h"
#include "TallPillar_Full_Prefab.h"
#include "TallPillar_Half_Prefab.h"
#include "TallPillar_Quarter_Prefab.h"

Room_2DoorStraight_Normal::Room_2DoorStraight_Normal(std::string name) : Entity(name)
{
	// Parent Prefab to build off from
	Entity* parentPrefab = new RoomPrefab_Straight("2DoorStraight_Base");
	this->AddChild(parentPrefab);


	// Adding Corner Pillars
	Entity* cornerPillar = new TallPillar_Quarter_Prefab("CornerPillar (1)");
	cornerPillar->GetTransform()->SetLocalPosition(glm::vec3(8.5f, 3.0f, 8.5f));
	cornerPillar->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 0.0f), glm::vec3(0, 1, 0)));
	this->AddChild(cornerPillar);

	cornerPillar = new TallPillar_Quarter_Prefab("CornerPillar (2)");
	cornerPillar->GetTransform()->SetLocalPosition(glm::vec3(-8.5f, 3.0f, 8.5f));
	cornerPillar->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 0.5f), glm::vec3(0, 1, 0)));
	this->AddChild(cornerPillar);

	cornerPillar = new TallPillar_Quarter_Prefab("CornerPillar (3)");
	cornerPillar->GetTransform()->SetLocalPosition(glm::vec3(-8.5f, 3.0f, -8.5f));
	cornerPillar->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 1.0f), glm::vec3(0, 1, 0)));
	this->AddChild(cornerPillar);

	cornerPillar = new TallPillar_Quarter_Prefab("CornerPillar (4)");
	cornerPillar->GetTransform()->SetLocalPosition(glm::vec3(8.5f, 3.0f, -8.5f));
	cornerPillar->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 1.5f), glm::vec3(0, 1, 0)));
	this->AddChild(cornerPillar);


	// Adding Corner Pillars
	Entity* sidePillar = new TallPillar_Half_Prefab("SidePillar (Front 1)");
	sidePillar->GetTransform()->SetLocalPosition(glm::vec3(2.5f, 3.0f, -8.5f));
	sidePillar->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 1.0f), glm::vec3(0, 1, 0)));
	this->AddChild(sidePillar);
	sidePillar = new TallPillar_Half_Prefab("SidePillar (Front 2)");
	sidePillar->GetTransform()->SetLocalPosition(glm::vec3(-2.5f, 3.0f, -8.5f));
	sidePillar->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 1.0f), glm::vec3(0, 1, 0)));
	this->AddChild(sidePillar);

	sidePillar = new TallPillar_Half_Prefab("SidePillar (Right 1)");
	sidePillar->GetTransform()->SetLocalPosition(glm::vec3(8.5f, 3.0f, -2.5f));
	sidePillar->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 1.5f), glm::vec3(0, 1, 0)));
	this->AddChild(sidePillar);
	sidePillar = new TallPillar_Half_Prefab("SidePillar (Right 2)");
	sidePillar->GetTransform()->SetLocalPosition(glm::vec3(8.5f, 3.0f, 2.5f));
	sidePillar->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 1.5f), glm::vec3(0, 1, 0)));
	this->AddChild(sidePillar);

	sidePillar = new TallPillar_Half_Prefab("SidePillar (Back 1)");
	sidePillar->GetTransform()->SetLocalPosition(glm::vec3(2.5f, 3.0f, 8.5f));
	sidePillar->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 0.0f), glm::vec3(0, 1, 0)));
	this->AddChild(sidePillar);
	sidePillar = new TallPillar_Half_Prefab("SidePillar (Back 2)");
	sidePillar->GetTransform()->SetLocalPosition(glm::vec3(-2.5f, 3.0f, 8.5f));
	sidePillar->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 0.0f), glm::vec3(0, 1, 0)));
	this->AddChild(sidePillar);

	sidePillar = new TallPillar_Half_Prefab("SidePillar (Left 1)");
	sidePillar->GetTransform()->SetLocalPosition(glm::vec3(-8.5f, 3.0f, 2.5f));
	sidePillar->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 0.5f), glm::vec3(0, 1, 0)));
	this->AddChild(sidePillar);
	sidePillar = new TallPillar_Half_Prefab("SidePillar (Left 2)");
	sidePillar->GetTransform()->SetLocalPosition(glm::vec3(-8.5f, 3.0f, -2.5f));
	sidePillar->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 0.5f), glm::vec3(0, 1, 0)));
	this->AddChild(sidePillar);


	// Adding Center Pillars
	Entity* middlePillar = new TallPillar_Full_Prefab("MiddlePillar (1)");
	middlePillar->GetTransform()->SetLocalPosition(glm::vec3(2.5f, 3.0f, 2.5f));
	this->AddChild(middlePillar);

	middlePillar = new TallPillar_Full_Prefab("MiddlePillar (2)");
	middlePillar->GetTransform()->SetLocalPosition(glm::vec3(-2.5f, 3.0f, 2.5f));
	this->AddChild(middlePillar);

	middlePillar = new TallPillar_Full_Prefab("MiddlePillar (3)");
	middlePillar->GetTransform()->SetLocalPosition(glm::vec3(-2.5f, 3.0f, -2.5f));
	this->AddChild(middlePillar);

	middlePillar = new TallPillar_Full_Prefab("MiddlePillar (4)");
	middlePillar->GetTransform()->SetLocalPosition(glm::vec3(2.5f, 3.0f, -2.5f));
	this->AddChild(middlePillar);
}