#include "MainCamera.h"


MainCamera::MainCamera() = default;

MainCamera::MainCamera(sf::Vector2f pivot)
{
	cameraView.setCenter(pivot);
}

MainCamera::~MainCamera() = default;

void MainCamera::Update(ECS::World* world, float deltaTime, sf::RenderWindow* gameWindow)
{
	// TODO: local instantiation (research)
	sf::Vector2f _windowSize(gameWindow->getSize().x, gameWindow->getSize().y);

	cameraView.setSize(_windowSize);

	float _cameraMoveSpeed = 0.1f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) == true)
	{
		cameraView.move(-_cameraMoveSpeed * deltaTime, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) == true)
	{
		cameraView.move(_cameraMoveSpeed * deltaTime, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) == true)
	{
		cameraView.move(0, -_cameraMoveSpeed * deltaTime);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) == true)
	{
		cameraView.move(0, _cameraMoveSpeed * deltaTime);
	}

	gameWindow->setView(cameraView);
}
