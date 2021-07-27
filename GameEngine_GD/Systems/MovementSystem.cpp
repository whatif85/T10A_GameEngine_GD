#include "MovementSystem.h"
//#include "../Interface/States.h"


MovementSystem::MovementSystem() {}

MovementSystem::~MovementSystem() {}

void MovementSystem::tick(ECS::World* world, float deltaTime)
{
	if (States::GetPausedState() == false)
	{
		world->each<InputController, Transform, Animator>(
			[&](ECS::Entity* entity,
				ECS::ComponentHandle<InputController> input,
				ECS::ComponentHandle<Transform> transform,
				ECS::ComponentHandle<Animator> animator) -> void
		{
			if (input->bInputActive == true)
			{
				// up
				if (input->wKey == true)
				{
					transform->ySpeed = -transform->ySpeedMod;
					transform->Move();
				}
				// down
				else if (input->sKey == true)
				{
					transform->ySpeed = transform->ySpeedMod;
					transform->Move();
				}
				// stop
				else
				{
					animator->currentRow = 0;
					transform->ySpeed = 0;
				}

				// left
				if (input->aKey == true)
				{
					animator->bFacingRight = false;
					animator->currentRow = 1;
					transform->xSpeed = -transform->xSpeedMod;
					transform->Move();
				}
				// right
				else if (input->dKey == true)
				{
					animator->bFacingRight = true;
					animator->currentRow = 1;
					transform->xSpeed = transform->xSpeedMod;
					transform->Move();
				}
				// stop
				else
				{
					animator->currentRow = 0;
					transform->xSpeed = 0;
				}
			}

			//printf("X: %f\nY: %f\n", transform->xPos, transform->yPos);
		});
	}
}
