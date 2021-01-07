#include "Room_3Door_NoLeft_TopFloor.h"

// Required Components
#include "DecorationSpawner.h"
#include "RoomController.h"

// Required Prefabs
#include "RoomPrefab_3Door.h"
#include "TallPillar_Half_Prefab.h"
#include "TallPillar_Quarter_Prefab.h"
#include "ShortPillar_Full_Prefab.h"
#include "TopFloor_Straight_Prefab.h"

Room_3Door_NoLeft_TopFloor::Room_3Door_NoLeft_TopFloor(std::string name) : Entity(name)
{
	// All Decorated Rooms Require a Controller
	this->AddComponent<RoomController>();


	// Parent Prefab to build off from
	Entity* parentPrefab = new RoomPrefab_3Door("3Door_Base");
	this->AddChild(parentPrefab);


	// Adding Corner Pillars
	Entity* cornerPillar = new TallPillar_Quarter_Prefab("CornerPillar (1)");
	cornerPillar->GetTransform()->SetLocalPosition(glm::vec3(8.5f, 3.5f, 8.5f));
	cornerPillar->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 0.0f), glm::vec3(0, 1, 0)));
	this->AddChild(cornerPillar);

	cornerPillar = new TallPillar_Quarter_Prefab("CornerPillar (2)");
	cornerPillar->GetTransform()->SetLocalPosition(glm::vec3(-8.5f, 3.5f, 8.5f));
	cornerPillar->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 0.5f), glm::vec3(0, 1, 0)));
	this->AddChild(cornerPillar);

	cornerPillar = new TallPillar_Quarter_Prefab("CornerPillar (3)");
	cornerPillar->GetTransform()->SetLocalPosition(glm::vec3(-8.5f, 3.5f, -8.5f));
	cornerPillar->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 1.0f), glm::vec3(0, 1, 0)));
	this->AddChild(cornerPillar);

	cornerPillar = new TallPillar_Quarter_Prefab("CornerPillar (4)");
	cornerPillar->GetTransform()->SetLocalPosition(glm::vec3(8.5f, 3.5f, -8.5f));
	cornerPillar->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 1.5f), glm::vec3(0, 1, 0)));
	this->AddChild(cornerPillar);


	// Adding Corner Pillars
	Entity* sidePillar = new TallPillar_Half_Prefab("SidePillar (Front 1)");
	sidePillar->GetTransform()->SetLocalPosition(glm::vec3(2.5f, 3.5f, -8.5f));
	sidePillar->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 1.0f), glm::vec3(0, 1, 0)));
	this->AddChild(sidePillar);
	sidePillar = new TallPillar_Half_Prefab("SidePillar (Front 2)");
	sidePillar->GetTransform()->SetLocalPosition(glm::vec3(-2.5f, 3.5f, -8.5f));
	sidePillar->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 1.0f), glm::vec3(0, 1, 0)));
	this->AddChild(sidePillar);

	sidePillar = new TallPillar_Half_Prefab("SidePillar (Right 1)");
	sidePillar->GetTransform()->SetLocalPosition(glm::vec3(8.5f, 3.5f, -2.5f));
	sidePillar->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 1.5f), glm::vec3(0, 1, 0)));
	this->AddChild(sidePillar);
	sidePillar = new TallPillar_Half_Prefab("SidePillar (Right 2)");
	sidePillar->GetTransform()->SetLocalPosition(glm::vec3(8.5f, 3.5f, 2.5f));
	sidePillar->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 1.5f), glm::vec3(0, 1, 0)));
	this->AddChild(sidePillar);

	sidePillar = new TallPillar_Half_Prefab("SidePillar (Back 1)");
	sidePillar->GetTransform()->SetLocalPosition(glm::vec3(2.5f, 3.5f, 8.5f));
	sidePillar->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 0.0f), glm::vec3(0, 1, 0)));
	this->AddChild(sidePillar);
	sidePillar = new TallPillar_Half_Prefab("SidePillar (Back 2)");
	sidePillar->GetTransform()->SetLocalPosition(glm::vec3(-2.5f, 3.5f, 8.5f));
	sidePillar->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 0.0f), glm::vec3(0, 1, 0)));
	this->AddChild(sidePillar);

	sidePillar = new TallPillar_Half_Prefab("SidePillar (Left 1)");
	sidePillar->GetTransform()->SetLocalPosition(glm::vec3(-8.5f, 3.5f, 2.5f));
	sidePillar->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 0.5f), glm::vec3(0, 1, 0)));
	this->AddChild(sidePillar);
	sidePillar = new TallPillar_Half_Prefab("SidePillar (Left 2)");
	sidePillar->GetTransform()->SetLocalPosition(glm::vec3(-8.5f, 3.5f, -2.5f));
	sidePillar->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((-3.14f * 0.5f), glm::vec3(0, 1, 0)));
	this->AddChild(sidePillar);


	// Adding Center Pillars
	Entity* middlePillar = new ShortPillar_Full_Prefab("MiddlePillar (1)");
	middlePillar->GetTransform()->SetLocalPosition(glm::vec3(2.5f, 1.75f, 2.5f));
	this->AddChild(middlePillar);

	middlePillar = new ShortPillar_Full_Prefab("MiddlePillar (2)");
	middlePillar->GetTransform()->SetLocalPosition(glm::vec3(2.5f, 1.75f, -2.5f));
	this->AddChild(middlePillar);


	// Adding Decorative Top Floor
	Entity* topFloor = new TopFloor_Straight_Prefab("TopFloor");
	topFloor->GetTransform()->SetLocalPosition(glm::vec3(0.0f, 3.0f, 0.0f));
	topFloor->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * 0.0f), glm::vec3(0, 1, 0)));
	this->AddChild(topFloor);


	// Adding Decoration/ Mimic Spawn Points
	// Table Set 1
	{
		// Main Table
		Entity* newSpawnPoint = new Entity("Spawn Point (1)");
		newSpawnPoint->GetTransform()->SetGlobalPosition(glm::vec3(-4.5f, 0, -4.0f));
		newSpawnPoint->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * 0.5f), glm::vec3(0, 1, 0)));
		this->AddChild(newSpawnPoint);

		newSpawnPoint->AddComponent<DecorationSpawner>();
		newSpawnPoint->GetComponent<DecorationSpawner>()->SetDecorationType(DecorationType::DECORATIONTYPE_TABLE);
		this->GetComponent<RoomController>()->AddDecorationSpawner(newSpawnPoint->GetComponent<DecorationSpawner>());

		// Chairs
		newSpawnPoint = new Entity("Spawn Point (2)");
		newSpawnPoint->GetTransform()->SetGlobalPosition(glm::vec3(-5.667f, 0, -2.5f));
		newSpawnPoint->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * 0.5f), glm::vec3(0, 1, 0)));
		this->AddChild(newSpawnPoint);

		newSpawnPoint->AddComponent<DecorationSpawner>();
		newSpawnPoint->GetComponent<DecorationSpawner>()->SetDecorationType(DecorationType::DECORATIONTYPE_CHAIR);
		this->GetComponent<RoomController>()->AddDecorationSpawner(newSpawnPoint->GetComponent<DecorationSpawner>());

		newSpawnPoint = new Entity("Spawn Point (3)");
		newSpawnPoint->GetTransform()->SetGlobalPosition(glm::vec3(-3.334f, 0, -2.5f));
		newSpawnPoint->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * 0.5f), glm::vec3(0, 1, 0)));
		this->AddChild(newSpawnPoint);

		newSpawnPoint->AddComponent<DecorationSpawner>();
		newSpawnPoint->GetComponent<DecorationSpawner>()->SetDecorationType(DecorationType::DECORATIONTYPE_CHAIR);
		this->GetComponent<RoomController>()->AddDecorationSpawner(newSpawnPoint->GetComponent<DecorationSpawner>());

		newSpawnPoint = new Entity("Spawn Point (4)");
		newSpawnPoint->GetTransform()->SetGlobalPosition(glm::vec3(-5.667f, 0, -5.5f));
		newSpawnPoint->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * 1.5f), glm::vec3(0, 1, 0)));
		this->AddChild(newSpawnPoint);

		newSpawnPoint->AddComponent<DecorationSpawner>();
		newSpawnPoint->GetComponent<DecorationSpawner>()->SetDecorationType(DecorationType::DECORATIONTYPE_CHAIR);
		this->GetComponent<RoomController>()->AddDecorationSpawner(newSpawnPoint->GetComponent<DecorationSpawner>());

		newSpawnPoint = new Entity("Spawn Point (5)");
		newSpawnPoint->GetTransform()->SetGlobalPosition(glm::vec3(-3.334f, 0, -5.5f));
		newSpawnPoint->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * 1.5f), glm::vec3(0, 1, 0)));
		this->AddChild(newSpawnPoint);

		newSpawnPoint->AddComponent<DecorationSpawner>();
		newSpawnPoint->GetComponent<DecorationSpawner>()->SetDecorationType(DecorationType::DECORATIONTYPE_CHAIR);
		this->GetComponent<RoomController>()->AddDecorationSpawner(newSpawnPoint->GetComponent<DecorationSpawner>());
	}

	// Table Set 2
	{
		// Main Table
		Entity* newSpawnPoint = new Entity("Spawn Point (1)");
		newSpawnPoint->GetTransform()->SetGlobalPosition(glm::vec3(-4.5f, 0, 4.0f));
		newSpawnPoint->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * 0.5f), glm::vec3(0, 1, 0)));
		this->AddChild(newSpawnPoint);

		newSpawnPoint->AddComponent<DecorationSpawner>();
		newSpawnPoint->GetComponent<DecorationSpawner>()->SetDecorationType(DecorationType::DECORATIONTYPE_TABLE);
		this->GetComponent<RoomController>()->AddDecorationSpawner(newSpawnPoint->GetComponent<DecorationSpawner>());

		// Chairs
		newSpawnPoint = new Entity("Spawn Point (2)");
		newSpawnPoint->GetTransform()->SetGlobalPosition(glm::vec3(-5.667f, 0, 2.5f));
		newSpawnPoint->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * 1.5f), glm::vec3(0, 1, 0)));
		this->AddChild(newSpawnPoint);

		newSpawnPoint->AddComponent<DecorationSpawner>();
		newSpawnPoint->GetComponent<DecorationSpawner>()->SetDecorationType(DecorationType::DECORATIONTYPE_CHAIR);
		this->GetComponent<RoomController>()->AddDecorationSpawner(newSpawnPoint->GetComponent<DecorationSpawner>());

		newSpawnPoint = new Entity("Spawn Point (3)");
		newSpawnPoint->GetTransform()->SetGlobalPosition(glm::vec3(-3.334f, 0, 2.5f));
		newSpawnPoint->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * 1.5f), glm::vec3(0, 1, 0)));
		this->AddChild(newSpawnPoint);

		newSpawnPoint->AddComponent<DecorationSpawner>();
		newSpawnPoint->GetComponent<DecorationSpawner>()->SetDecorationType(DecorationType::DECORATIONTYPE_CHAIR);
		this->GetComponent<RoomController>()->AddDecorationSpawner(newSpawnPoint->GetComponent<DecorationSpawner>());

		newSpawnPoint = new Entity("Spawn Point (4)");
		newSpawnPoint->GetTransform()->SetGlobalPosition(glm::vec3(-5.667f, 0, 5.5f));
		newSpawnPoint->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * 0.5f), glm::vec3(0, 1, 0)));
		this->AddChild(newSpawnPoint);

		newSpawnPoint->AddComponent<DecorationSpawner>();
		newSpawnPoint->GetComponent<DecorationSpawner>()->SetDecorationType(DecorationType::DECORATIONTYPE_CHAIR);
		this->GetComponent<RoomController>()->AddDecorationSpawner(newSpawnPoint->GetComponent<DecorationSpawner>());

		newSpawnPoint = new Entity("Spawn Point (5)");
		newSpawnPoint->GetTransform()->SetGlobalPosition(glm::vec3(-3.334f, 0, 5.5f));
		newSpawnPoint->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * 0.5f), glm::vec3(0, 1, 0)));
		this->AddChild(newSpawnPoint);

		newSpawnPoint->AddComponent<DecorationSpawner>();
		newSpawnPoint->GetComponent<DecorationSpawner>()->SetDecorationType(DecorationType::DECORATIONTYPE_CHAIR);
		this->GetComponent<RoomController>()->AddDecorationSpawner(newSpawnPoint->GetComponent<DecorationSpawner>());
	}
}