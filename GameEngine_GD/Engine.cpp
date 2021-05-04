#include "Engine.h"


Engine::Engine() = default;

Engine::~Engine() = default;

void Engine::Start(sf::RenderWindow* win)
{
	bQuit = false;
	this->window = win;

	// Run the program as long as the window is open
	while (window->isOpen() == true)
	{
		Update();
	}
}

Engine& Engine::GetInstance()
{
	static Engine _instance;

	return _instance;
}

void Engine::Update()
{
	sf::Event _event;

	while (window->pollEvent(_event) == true)
	{
		// close requested event
		if (_event.type == sf::Event::Closed)
		{
			window->close();
		}
	}
}
