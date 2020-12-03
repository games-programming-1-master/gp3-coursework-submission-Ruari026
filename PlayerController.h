#pragma once
#include "Component.h"
#include "Entity.h"

class PlayerController : public Component
{
private:

public:
	void OnUpdate(float deltaTime);
};