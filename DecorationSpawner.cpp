#include "DecorationSpawner.h"

// Regular Decoration Prefabs
#include "Chair_Prefab.h"
#include "Table_Prefab.h"
#include "Hedge_Small_Prefab.h"
#include "Hedge_Large_Prefab.h"

// Enemy Mimic Prefabs
#include "ChairMimic_Prefab.h"
#include "TableMimic_Prefab.h"
#include "HedgeMimic_Small_Prefab.h"
#include "HedgeMimic_Large_Prefab.h"

DecorationSpawner::DecorationSpawner()
{
}

DecorationSpawner::~DecorationSpawner()
{
}


/*
========================================================================================================================================================================================================
Inherited Entity Methods
========================================================================================================================================================================================================
*/
void DecorationSpawner::OnStart()
{
}

void DecorationSpawner::OnUpdate(float deltaTime)
{
}

void DecorationSpawner::OnRender()
{
}


/*
========================================================================================================================================================================================================
Decoration Spawning
========================================================================================================================================================================================================
*/
void DecorationSpawner::SpawnDecoration()
{
	switch (decorationToSpawn)
	{
		case (DecorationType::DECORATIONTYPE_CHAIR):
		{
			// Spawning prefab
			Entity* newChair = new Chair_Prefab("Chair Decoration");
			this->m_entity->AddChild(newChair);

			// Need to adjust y position for chair height
			newChair->GetTransform()->SetLocalPosition(glm::vec3(0, 1.05f, 0));
		}
		break;


		case (DecorationType::DECORATIONTYPE_TABLE):
		{
			// Spawning prefab
			Entity* newTable = new Table_Prefab("Table Decoration");
			this->m_entity->AddChild(newTable);

			// Need to adjust y position for table height
			newTable->GetTransform()->SetLocalPosition(glm::vec3(0, 0.55f, 0));
		}
		break;


		case (DecorationType::DECORATIONTYPE_CRATE):
		{

		}
		break;


		case (DecorationType::DECORATIONTYPE_SMALLHEDGE):
		{
			// Spawning prefab
			Entity* newHedge = new Hedge_Small_Prefab("Small Hedge Decoration");
			this->m_entity->AddChild(newHedge);

			// Need to adjust y position for hedge height
			newHedge->GetTransform()->SetLocalPosition(glm::vec3(0, 0.875f, 0));
		}
		break;


		case (DecorationType::DECORATIONTYPE_LARGEHEDGE):
		{
			// Spawning prefab
			Entity* newHedge = new Hedge_Large_Prefab("Large Hedge Decoration");
			this->m_entity->AddChild(newHedge);

			// Need to adjust y position for hedge height
			newHedge->GetTransform()->SetLocalPosition(glm::vec3(0, 0.875f, 0));
		}
		break;
	}
}

void DecorationSpawner::SpawnMimic()
{
	switch (decorationToSpawn)
	{
		case (DecorationType::DECORATIONTYPE_CHAIR):
		{
			// Spawning prefab
			Entity* newChair = new ChairMimic_Prefab("Chair Mimic");
			this->m_entity->AddChild(newChair);

			// Need to adjust y position for chair height
			newChair->GetTransform()->SetLocalPosition(glm::vec3(0, 4.05f, 0));
		}
		break;


		case (DecorationType::DECORATIONTYPE_TABLE):
		{
			// Spawning prefab
			Entity* newTable = new TableMimic_Prefab("Table Mimic");
			this->m_entity->AddChild(newTable);

			// Need to adjust y position for table height
			newTable->GetTransform()->SetLocalPosition(glm::vec3(0, 3.55f, 0));
		}
		break;


		case (DecorationType::DECORATIONTYPE_CRATE):
		{

		}
		break;


		case (DecorationType::DECORATIONTYPE_SMALLHEDGE):
		{
			// Spawning prefab
			Entity* newHedge = new HedgeMimic_Small_Prefab("Small Hedge Mimic");
			this->m_entity->AddChild(newHedge);

			// Need to adjust y position for hedge height
			newHedge->GetTransform()->SetLocalPosition(glm::vec3(0, 1.125f, 0));
		}
		break;


		case (DecorationType::DECORATIONTYPE_LARGEHEDGE):
		{
			// Spawning prefab
			Entity* newHedge = new HedgeMimic_Large_Prefab("Large Hedge Mimic");
			this->m_entity->AddChild(newHedge);

			// Need to adjust y position for hedge height
			newHedge->GetTransform()->SetLocalPosition(glm::vec3(0, 1.125f, 0));
		}
		break;
	}
}