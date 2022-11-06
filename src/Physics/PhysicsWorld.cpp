#include <Physics/PhysicsWorld.h>


void Physics::PhysicsWorld::AddObject(Physics::PhysicsObject* object)
{
	m_PhysicsObjects.push_back(object);
}

void Physics::PhysicsWorld::RemoveObject(Physics::PhysicsObject* object)
{
	m_PhysicsObjects.erase(std::remove(m_PhysicsObjects.begin(), m_PhysicsObjects.end(), object), m_PhysicsObjects.end());
}

void Physics::PhysicsWorld::Step(float ts)
{
	for (Physics::PhysicsObject* obj : m_PhysicsObjects) {
		if (obj->IS_STATIC) continue;

		obj->SetForce(obj->GetForce() + obj->GetMass() * m_gravity);
		obj->Update(ts);
	}
}