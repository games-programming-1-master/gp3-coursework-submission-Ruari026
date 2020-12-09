#pragma once
#include "CollisionShape.h"
class SphereShape : public CollisionShape
{
private:
	float m_radius;
public:
	SphereShape(float radius);
};