#pragma once

#include <SFML/Graphics.hpp>
#include "ECS.h"

#include "Components.h"


#include "Interface/States.h"
#include "Interface/Button.h"
#include "Interface/ButtonMap.h"
#include "Interface/PauseMenu.h"
#include "Interface/MainCamera.h"

#include "Systems/RenderingSystem.h"
#include "Systems/AnimationSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/PhysicsSystem.h"
#include "Systems/TileMapSystem.h"


class Engine
{
public:
	sf::RenderWindow* window;
	ECS::World* world;

	class MainCamera mainCamera;
	class PauseMenu pauseMenu;

	void Start(sf::RenderWindow* win);
	void AddSystem(ECS::EntitySystem* newSys);

	// Singleton pattern: Only instantiate the engine once
	static Engine& GetInstance();

private:
	bool bQuit;

	Engine();

	// Required to prevent the reference from being copied, moved, or assigned
	Engine(Engine& copy);		// hide copy constructor
	Engine(Engine&& move);		// hide move constructor
	Engine& operator= (Engine& copy); // hide assignment operator

	~Engine();

	void Update();

	void OnGameInactiveState();
};

