#include <Physics/PhysicsCollider.h>

using namespace Physics;

PhysicsRectangeCollider::PhysicsRectangeCollider(Transform transform)
	:	PhysicsCollider(transform)
{

}

bool PhysicsRectangeCollider::CheckCollision_Rectangle_Rectangle(Transform* rectangleT1, Transform* rectangleT2)
{
	return true;
}