#include "Engine.h"


Engine::Engine() = default;

Engine::~Engine() = default;

void Engine::Start(sf::RenderWindow* win)
{
	bQuit = false;
	this->window = win;

	mainCamera = MainCamera(sf::Vector2f(
		this->window->getSize().x / 2,
		this->window->getSize().y / 2));

	pauseMenu = PauseMenu(this->window);

	// Run the program as long as the window is open
	while (window->isOpen() == true)
	{
		Update();
	}
}

void Engine::AddSystem(ECS::EntitySystem* newSys)
{
	world->registerSystem(newSys);
	world->enableSystem(newSys);
}

Engine& Engine::GetInstance()
{
	static Engine _instance;

	return _instance;
}

void Engine::Update()
{
	sf::Event _event;

	// listen to any event occurring while the program
	while (window->pollEvent(_event) == true)
	{
		// close requested event
		if (_event.type == sf::Event::Closed)
		{
			window->close();

			exit(EXIT_SUCCESS);
		}

		pauseMenu.Update(_event, 10.0f, window);
	}

	world->tick(10.0f);

	mainCamera.Update(world, 10.0f, window);

	if (States::GetPausedState() == true)
	{
		OnGameInactiveState();
	}
}

void Engine::OnGameInactiveState()
{
	pauseMenu.Render(window, 10.0f, mainCamera.cameraView.getCenter());
}
