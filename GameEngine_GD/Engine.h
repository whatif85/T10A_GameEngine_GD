#pragma once

#include <SFML/Graphics.hpp>


class Engine
{
public:
	sf::RenderWindow* window;

	void Start(sf::RenderWindow* win);

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
};

