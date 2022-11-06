#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>
#include <Physics/PhysicsObject.h>


namespace Physics
{
	class PhysicsWorld {
	private:
		std::vector<Physics::PhysicsObject*> m_PhysicsObjects;
		glm::vec3 m_gravity = { 0.0f, 9.81f, 0.0f };

	public:
		void AddObject(Physics::PhysicsObject* object);
		void RemoveObject(Physics::PhysicsObject* object);

		void Step(float ts);
	};
}