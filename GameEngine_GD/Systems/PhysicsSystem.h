#pragma once

#include "../Engine.h"


class PhysicsSystem : public ECS::EntitySystem
{
public:
	PhysicsSystem();
	~PhysicsSystem();

	bool IsColliding(
		ECS::ComponentHandle<struct BoxCollider> touchingBox,
		ECS::ComponentHandle<struct BoxCollider> touchedBox,
		float x, float y
	);
	bool IsColliding(
		ECS::ComponentHandle<struct BoxCollider> touchingBox,
		sf::RectangleShape touchedRectangle, float x, float y
	);
	bool IsColliding(
		ECS::ComponentHandle<struct BoxCollider> touchingBox,
		sf::RectangleShape touchedRectangle
	);
	bool IsColliding(
		ECS::ComponentHandle<struct BoxCollider> touchingBox,
		ECS::ComponentHandle<struct BoxCollider> touchedBox
	);

	void CheckCollisionSides(
		ECS::ComponentHandle<struct Transform> tranform,
		ECS::ComponentHandle<struct BoxCollider> touchingBox,
		ECS::ComponentHandle<struct BoxCollider> touchedBox
	);
	void CheckCollisionSides(
		ECS::ComponentHandle<struct Transform> transform,
		ECS::ComponentHandle<struct BoxCollider> touchingBox,
		sf::RectangleShape touchedRectangle
	);

	void CheckCollisionSides(
		ECS::Entity* touchingEntity,
		ECS::Entity* touchedEntity
	);

	void tick(ECS::World* world, float deltaTime) override;
};



