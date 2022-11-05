#include <Physics/PhysicsObject.h>

#include <iostream>
Physics::PhysicsObject::PhysicsObject(glm::vec3 postion)
	: m_Position(postion)
{
}

Physics::PhysicsObject::~PhysicsObject()
{
}

void Physics::PhysicsObject::Update(float dt)
{
	m_Velocity += m_Force / m_Mass * dt;
	m_Position += m_Velocity * dt;
	m_Force = { 0.0f, 0.0f, 0.0f };
}
