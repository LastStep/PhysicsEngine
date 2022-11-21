#pragma once
#include <memory>

#include <glm/glm.hpp>


namespace Physics
{
	struct Transform
	{
		glm::vec3 Position;
		glm::vec3 Scale;
	};

	class PhysicsCollider
	{
	public:
		std::shared_ptr<Transform> m_Transform;

		PhysicsCollider(Transform transform) 
			:	m_Transform(std::make_shared<Transform>(transform))
		{
		};

		virtual bool CheckCollision_Rectangle_Rectangle(Transform* rectangleT1, Transform* rectangleT2) = 0;
	};

	class PhysicsRectangeCollider : public PhysicsCollider
	{
	public:
		PhysicsRectangeCollider(Transform transform);

		bool CheckCollision_Rectangle_Rectangle(Transform* rectangleT1, Transform* rectangleT2) override;
	};
}