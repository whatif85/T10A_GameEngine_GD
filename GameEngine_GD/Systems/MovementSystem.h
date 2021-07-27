#pragma once

#include "../Engine.h"


class MovementSystem
	: public ECS::EntitySystem
{
public:
	MovementSystem();
	~MovementSystem();

	void tick(ECS::World* world, float deltaTime) override;
};

