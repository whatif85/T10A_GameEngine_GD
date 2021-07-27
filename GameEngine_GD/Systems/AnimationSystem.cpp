#include "AnimationSystem.h"
#include <iostream>

AnimationSystem::AnimationSystem() = default;

AnimationSystem::~AnimationSystem() = default;

void AnimationSystem::tick(ECS::World * world, float deltaTime)
{
	if (States::GetPausedState() == false)
	{
		world->each<struct Animator, struct Sprite2D>(
			[&](ECS::Entity* entity,
				ECS::ComponentHandle<Animator> animator,
				ECS::ComponentHandle<Sprite2D> sprite) -> void
		{
			animator->currentTime += deltaTime;

			if (animator->currentTime >= animator->nextFrameTime)
			{
				animator->currentTime = 0;
				animator->currentColumn = (animator->currentColumn + 1) % animator->totalColumns;
			}

			// size of 1 frame per sprite
			sprite->self.setTextureRect(
				sf::IntRect(
					animator->currentColumn * animator->spriteWidth, // Left / right sides
					animator->currentRow * animator->spriteHeight, // Top / Bottom sides
					animator->spriteWidth,
					animator->spriteHeight
				)
			);
		});
	}
}
