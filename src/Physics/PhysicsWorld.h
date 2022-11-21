#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>
#include <Physics/PhysicsObject.h>


namespace Physics
{
	class PhysicsWorld 
	{
	private:
		std::vector<Physics::PhysicsObject*> m_PhysicsObjects;

		struct WorldConstants
		{
			glm::vec3 Gravity = { 0.0f, 9.81f, 0.0f };
			float SpeedFactor = 50.0f;
		};
		WorldConstants m_WorldConstants{};

	public:
		void AddObject(Physics::PhysicsObject* object);
		void RemoveObject(Physics::PhysicsObject* object);

		void Step(float ts);
	};
}