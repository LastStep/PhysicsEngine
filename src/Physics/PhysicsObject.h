#pragma once

#include <glm/glm.hpp>

#include <Physics/PhysicsCollider.h>


namespace Physics
{
	class PhysicsObject
	{

	private:
		float m_Mass = 1.0f;
		glm::vec3 m_Velocity = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Force = { 0.0f, 0.0f, 0.0f };

		float m_VelocityFactor = 10.0f;

		Transform m_Transform;

	public:
		bool IS_STATIC = false;

		PhysicsObject(glm::vec3 postion, glm::vec3 scale);
		~PhysicsObject();

		glm::vec3 GetPosition();

		inline float GetMass() { return m_Mass; }
		inline glm::vec3 GetForce() { return m_Force; }
		
		inline void SetForce(glm::vec3 force) { m_Force = force; }

		void Update(float dt);
	};
}