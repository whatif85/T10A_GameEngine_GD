#pragma once

#include "../Engine.h"


class AnimationSystem : public ECS::EntitySystem
{
public:
	AnimationSystem();
	~AnimationSystem();

private:
	void tick(ECS::World* world, float deltaTime) override;
};

