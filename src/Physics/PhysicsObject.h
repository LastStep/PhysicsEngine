#pragma once

#include <glm/glm.hpp>


namespace Physics
{
	class PhysicsObject
	{

	private:
		float m_Mass = 1.0f;
		glm::vec3 m_Position;
		glm::vec3 m_Velocity = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Force = { 0.0f, 0.0f, 0.0f };

	public:
		PhysicsObject(glm::vec3 postion);
		~PhysicsObject();

		inline float GetMass() { return m_Mass; }
		inline glm::vec3 GetPosition() { return m_Position; }
		inline glm::vec3 GetVelocity() { return m_Velocity; }
		inline glm::vec3 GetForce() { return m_Force; }

		inline void SetMass(float mass) { m_Mass = mass; }
		inline void SetPosition(glm::vec3 position) { m_Position = position; }
		inline void SetVelocity(glm::vec3 velocity) { m_Velocity = velocity; }
		inline void SetForce(glm::vec3 force) { m_Force = force; }

		void Update(float dt);
	};
}