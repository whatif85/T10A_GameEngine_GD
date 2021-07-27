#include "PauseMenu.h"


PauseMenu::PauseMenu() = default;

PauseMenu::PauseMenu(sf::RenderWindow* window)
{
	States::SetPausedState(false);
	InitButtons();
}

PauseMenu::~PauseMenu() = default;

void PauseMenu::Update(sf::Event event, float deltaTime, sf::RenderWindow * window)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			States::SetPausedState(States::GetPausedState() == false);
			std::printf("Is paused? %d\n", States::GetPausedState() ? 1 : 0);
		}
	}

	if (States::GetPausedState() == true)
	{
		std::printf("Game Paused\n");

		ButtonMap::GetMap()["RESUME"]->Update(event, deltaTime);
		ButtonMap::GetMap()["LOAD"]->Update(event, deltaTime);
		ButtonMap::GetMap()["SAVE"]->Update(event, deltaTime);
		ButtonMap::GetMap()["QUIT"]->Update(event, deltaTime);

		if (ButtonMap::GetMap()["RESUME"]->bClicked == true)
		{
			States::SetPausedState(States::GetPausedState() == false);
			ButtonMap::GetMap()["RESUME"]->bClicked = false;
		}

		if (ButtonMap::GetMap()["QUIT"]->bClicked == true)
		{
			Quit(window);
			ButtonMap::GetMap()["QUIT"]->bClicked = false;
		}
	}
}

void PauseMenu::Render(sf::RenderWindow * window, float deltaTime, sf::Vector2f resumePosition)
{
	sf::Font _arial;
	_arial.loadFromFile("../Debug/Fonts/arial.ttf");

	sf::Vector2f _sizeOffset = sf::Vector2f(
		ButtonMap::GetMap()["RESUME"]->buttonBG.getSize().x / 2,
		ButtonMap::GetMap()["RESUME"]->buttonBG.getSize().y / 2);

	// Resume button
	ButtonMap::GetMap()["RESUME"]->buttonBG.setPosition(resumePosition + sf::Vector2f(0, -80) - _sizeOffset);
	ButtonMap::GetMap()["RESUME"]->buttonText.setFont(_arial);
	ButtonMap::GetMap()["RESUME"]->buttonText.setPosition(ButtonMap::GetMap()["RESUME"]->buttonBG.getPosition());
	ButtonMap::GetMap()["RESUME"]->Highlight(window);
	ButtonMap::GetMap()["RESUME"]->Render(window, deltaTime);

	// Load button
	ButtonMap::GetMap()["LOAD"]->buttonBG.setPosition(resumePosition + sf::Vector2f(0, -40) - _sizeOffset);
	ButtonMap::GetMap()["LOAD"]->buttonText.setFont(_arial);
	ButtonMap::GetMap()["LOAD"]->buttonText.setPosition(ButtonMap::GetMap()["LOAD"]->buttonBG.getPosition());
	ButtonMap::GetMap()["LOAD"]->Highlight(window);
	ButtonMap::GetMap()["LOAD"]->Render(window, deltaTime);

	// Save button
	ButtonMap::GetMap()["SAVE"]->buttonBG.setPosition(resumePosition + sf::Vector2f(0, 0) - _sizeOffset);
	ButtonMap::GetMap()["SAVE"]->buttonText.setFont(_arial);
	ButtonMap::GetMap()["SAVE"]->buttonText.setPosition(ButtonMap::GetMap()["SAVE"]->buttonBG.getPosition());
	ButtonMap::GetMap()["SAVE"]->Highlight(window);
	ButtonMap::GetMap()["SAVE"]->Render(window, deltaTime);

	// Quit button
	ButtonMap::GetMap()["QUIT"]->buttonBG.setPosition(resumePosition + sf::Vector2f(0, 40) - _sizeOffset);
	ButtonMap::GetMap()["QUIT"]->buttonText.setFont(_arial);
	ButtonMap::GetMap()["QUIT"]->buttonText.setPosition(ButtonMap::GetMap()["QUIT"]->buttonBG.getPosition());
	ButtonMap::GetMap()["QUIT"]->Highlight(window);
	ButtonMap::GetMap()["QUIT"]->Render(window, deltaTime);

	window->display();
}

void PauseMenu::InitButtons(/*sf::RenderWindow* wnd*/)
{
	sf::Vector2f _size = sf::Vector2f(125, 30); /*= static_cast<sf::Vector2f>(wnd->getSize().x, wnd->getSize().y)*/

	ButtonMap::GetMap().insert(
		{
			"RESUME",
			new Button(_size, sf::Color(100, 100, 100, 255), "Resume Game")
		});

	ButtonMap::GetMap().insert(
		{
			"LOAD",
			new Button(_size, sf::Color(100, 100, 100, 255), "Load TileMap")
		});

	ButtonMap::GetMap().insert(
		{
			"SAVE",
			new Button(_size, sf::Color(100, 100, 100, 255), "Save TileMap")
		});

	ButtonMap::GetMap().insert(
		{
			"QUIT",
			new Button(_size, sf::Color(100, 100, 100, 255), "Quit Game")
		});
}

void PauseMenu::Quit(sf::RenderWindow * window)
{
	window->close();
}
