#include <SFML/Graphics.hpp>
#include "Engine.h"

int main(int argc, char* args[])
{
	// Declare and get instance of singleton
	Engine& gameEngine = Engine::GetInstance();

	sf::RenderWindow window(sf::VideoMode(800, 600), "Game Engine");

	// Pass instance to engine and start
	gameEngine.Start(&window);

	return 0;
}