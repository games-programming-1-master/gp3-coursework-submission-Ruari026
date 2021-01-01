#include "DecorationSpawner.h"

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

		}
		break;


		case (DecorationType::DECORATIONTYPE_TABLE):
		{

		}
		break;


		case (DecorationType::DECORATIONTYPE_CRATE):
		{

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

		}
		break;


		case (DecorationType::DECORATIONTYPE_TABLE):
		{

		}
		break;


		case (DecorationType::DECORATIONTYPE_CRATE):
		{

		}
		break;
	}
}