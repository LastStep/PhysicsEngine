#include <Physics/PhysicsWorld.h>

using namespace Physics;

void PhysicsWorld::AddObject(PhysicsObject* object)
{
	m_PhysicsObjects.push_back(object);
}

void PhysicsWorld::RemoveObject(PhysicsObject* object)
{
	m_PhysicsObjects.erase(std::remove(m_PhysicsObjects.begin(), m_PhysicsObjects.end(), object), m_PhysicsObjects.end());
}

void PhysicsWorld::Step(float ts)
{
	for (PhysicsObject* obj : m_PhysicsObjects) {
		if (obj->IS_STATIC) continue;

		obj->SetForce(obj->GetForce() + obj->GetMass() * m_WorldConstants.Gravity);
		obj->Update(ts);
	}
}