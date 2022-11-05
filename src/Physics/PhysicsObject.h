#pragma once

#include <Physics/Core.h>


class PhysicsObject
{

private:
	glm::vec3 m_Position;
	glm::vec3 m_Velocity = { 0.0f, 0.0f, 0.0f };
	glm::vec3 m_Force = { 0.0f, 0.0f, 0.0f };

public:
	//PhysicsObject();
	//~PhysicsObject();

	inline glm::vec3 GetPosition() { return m_Position; }
	inline glm::vec3 GetVelocity() { return m_Velocity; }
	inline glm::vec3 GetForce() { return m_Force; }

};