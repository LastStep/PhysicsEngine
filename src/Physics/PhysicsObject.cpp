#include <Physics/PhysicsObject.h>

using namespace Physics;

PhysicsObject::PhysicsObject(glm::vec3 postion, glm::vec3 scale)
	:	m_Transform({ postion, scale })
{
}

PhysicsObject::~PhysicsObject()
{
}

void PhysicsObject::Update(float dt)
{
	m_Velocity += m_VelocityFactor * (m_Force / m_Mass * dt);
	m_Transform.Position += m_Velocity * dt;
	m_Force = { 0.0f, 0.0f, 0.0f };
}

glm::vec3 PhysicsObject::GetPosition()
{
	return m_Transform.Position;
}