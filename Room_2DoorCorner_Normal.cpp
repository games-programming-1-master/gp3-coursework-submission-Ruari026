#include "Room_2DoorCorner_Normal.h"

// Required Components
#include "DecorationSpawner.h"
#include "RoomController.h"

// Required Prefabs
#include "RoomPrefab_Corner.h"
#include "TallPillar_Full_Prefab.h"
#include "TallPillar_Half_Prefab.h"
#include "TallPillar_Quarter_Prefab.h"
#include "DecorationSpawner.h"
#include "Table_Prefab.h"

Room_2DoorCorner_Normal::Room_2DoorCorner_Normal(std::string name) : Entity(name)
{
	// All Decorated Rooms Require a Controller
	this->AddComponent<RoomController>();


	// Parent Prefab to build off from
	Entity* parentPrefab = new RoomPrefab_Corner("2DoorCorner_Base");
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
	Entity* middlePillar = new TallPillar_Full_Prefab("MiddlePillar (1)");
	middlePillar->GetTransform()->SetLocalPosition(glm::vec3(2.5f, 3.5f, 2.5f));
	this->AddChild(middlePillar);

	middlePillar = new TallPillar_Full_Prefab("MiddlePillar (2)");
	middlePillar->GetTransform()->SetLocalPosition(glm::vec3(-2.5f, 3.5f, 2.5f));
	this->AddChild(middlePillar);

	middlePillar = new TallPillar_Full_Prefab("MiddlePillar (3)");
	middlePillar->GetTransform()->SetLocalPosition(glm::vec3(-2.5f, 3.5f, -2.5f));
	this->AddChild(middlePillar);

	middlePillar = new TallPillar_Full_Prefab("MiddlePillar (4)");
	middlePillar->GetTransform()->SetLocalPosition(glm::vec3(2.5f, 3.5f, -2.5f));
	this->AddChild(middlePillar);


	// Adding Decoration/ Mimic Spawn Points
	// Hedge Walls
	{
		Entity* newSpawnPoint = new Entity("Spawn Point (1)");
		newSpawnPoint->GetTransform()->SetGlobalPosition(glm::vec3(2.5f, 0, 5.75f));
		newSpawnPoint->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * 0.0f), glm::vec3(0, 1, 0)));
		this->AddChild(newSpawnPoint);

		newSpawnPoint->AddComponent<DecorationSpawner>();
		newSpawnPoint->GetComponent<DecorationSpawner>()->SetDecorationType(DecorationType::DECORATIONTYPE_LARGEHEDGE);
		this->GetComponent<RoomController>()->AddDecorationSpawner(newSpawnPoint->GetComponent<DecorationSpawner>());


		newSpawnPoint = new Entity("Spawn Point (2)");
		newSpawnPoint->GetTransform()->SetGlobalPosition(glm::vec3(-2.5f, 0, -5.75f));
		newSpawnPoint->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * 0.0f), glm::vec3(0, 1, 0)));
		this->AddChild(newSpawnPoint);

		newSpawnPoint->AddComponent<DecorationSpawner>();
		newSpawnPoint->GetComponent<DecorationSpawner>()->SetDecorationType(DecorationType::DECORATIONTYPE_LARGEHEDGE);
		this->GetComponent<RoomController>()->AddDecorationSpawner(newSpawnPoint->GetComponent<DecorationSpawner>());


		newSpawnPoint = new Entity("Spawn Point (3)");
		newSpawnPoint->GetTransform()->SetGlobalPosition(glm::vec3(0, 0, -2.5f));
		newSpawnPoint->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * 0.5f), glm::vec3(0, 1, 0)));
		this->AddChild(newSpawnPoint);

		newSpawnPoint->AddComponent<DecorationSpawner>();
		newSpawnPoint->GetComponent<DecorationSpawner>()->SetDecorationType(DecorationType::DECORATIONTYPE_LARGEHEDGE);
		this->GetComponent<RoomController>()->AddDecorationSpawner(newSpawnPoint->GetComponent<DecorationSpawner>());


		newSpawnPoint = new Entity("Spawn Point (4)");
		newSpawnPoint->GetTransform()->SetGlobalPosition(glm::vec3(-2.5f, 0, 0));
		newSpawnPoint->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * 0.0f), glm::vec3(0, 1, 0)));
		this->AddChild(newSpawnPoint);

		newSpawnPoint->AddComponent<DecorationSpawner>();
		newSpawnPoint->GetComponent<DecorationSpawner>()->SetDecorationType(DecorationType::DECORATIONTYPE_LARGEHEDGE);
		this->GetComponent<RoomController>()->AddDecorationSpawner(newSpawnPoint->GetComponent<DecorationSpawner>());
	}


	// Tables (To not be mimics)
	{
		Entity* newTable = new Table_Prefab("Table (1)");
		newTable->GetTransform()->SetGlobalPosition(glm::vec3(5.75f, 0.55f, 7.75f));
		newTable->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * 0.5f), glm::vec3(0, 1, 0)));
		this->AddChild(newTable);


		newTable = new Table_Prefab("Table (2)");
		newTable->GetTransform()->SetGlobalPosition(glm::vec3(-5.75f, 0.55f, -7.75f));
		newTable->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * 0.5f), glm::vec3(0, 1, 0)));
		this->AddChild(newTable);
	}


	// Chairs
	{
		Entity* newChair = new Entity("Spawn Point (1)");
		newChair->GetTransform()->SetGlobalPosition(glm::vec3((5.75f - 1.167f), 0, 6.25f));
		newChair->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * -0.5f), glm::vec3(0, 1, 0)));
		this->AddChild(newChair);

		newChair->AddComponent<DecorationSpawner>();
		newChair->GetComponent<DecorationSpawner>()->SetDecorationType(DecorationType::DECORATIONTYPE_CHAIR);
		this->GetComponent<RoomController>()->AddDecorationSpawner(newChair->GetComponent<DecorationSpawner>());


		newChair = new Entity("Spawn Point (2)");
		newChair->GetTransform()->SetGlobalPosition(glm::vec3((5.75f + 1.167f), 0, 6.25f));
		newChair->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * -0.5f), glm::vec3(0, 1, 0)));
		this->AddChild(newChair);

		newChair->AddComponent<DecorationSpawner>();
		newChair->GetComponent<DecorationSpawner>()->SetDecorationType(DecorationType::DECORATIONTYPE_CHAIR);
		this->GetComponent<RoomController>()->AddDecorationSpawner(newChair->GetComponent<DecorationSpawner>());

		newChair = new Entity("Spawn Point (3)");
		newChair->GetTransform()->SetGlobalPosition(glm::vec3((-5.75f - 1.167f), 0, -6.25f));
		newChair->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * 0.5f), glm::vec3(0, 1, 0)));
		this->AddChild(newChair);

		newChair->AddComponent<DecorationSpawner>();
		newChair->GetComponent<DecorationSpawner>()->SetDecorationType(DecorationType::DECORATIONTYPE_CHAIR);
		this->GetComponent<RoomController>()->AddDecorationSpawner(newChair->GetComponent<DecorationSpawner>());


		newChair = new Entity("Spawn Point (4)");
		newChair->GetTransform()->SetGlobalPosition(glm::vec3((-5.75f + 1.167f), 0, -6.25f));
		newChair->GetTransform()->SetLocalRotationQuaternion(Utility::GetRotationQuaternion((M_PI * 0.5f), glm::vec3(0, 1, 0)));
		this->AddChild(newChair);

		newChair->AddComponent<DecorationSpawner>();
		newChair->GetComponent<DecorationSpawner>()->SetDecorationType(DecorationType::DECORATIONTYPE_CHAIR);
		this->GetComponent<RoomController>()->AddDecorationSpawner(newChair->GetComponent<DecorationSpawner>());
	}
}