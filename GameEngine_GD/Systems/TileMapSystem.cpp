#include "TileMapSystem.h"

TileMapSystem::TileMapSystem() = default;
TileMapSystem::~TileMapSystem() = default;

void TileMapSystem::tick(ECS::World * world, float deltaTime)
{
	if (States::GetPausedState() == false)
	{
		Engine::GetInstance().world->each<TileMap>(
			[&](ECS::Entity* entity,
				ECS::ComponentHandle<TileMap> tileMap) -> void
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				AddTileOnClick(true, tileMap);
				//std::cout << entity->getEntityId() << " is the entity ID." << std::endl;
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				AddTileOnClick(false, tileMap);
				//std::cout << entity->getEntityId() << " is the entity ID." << std::endl;
				// TODO: All tile entities are 1
			}

			if (ButtonMap::GetMap()["SAVE"]->bClicked == true)
			{
				std::cout << "Save" << "\n";
				tileMap->SaveTileMap("TileTest.txt");
				ButtonMap::GetMap()["SAVE"]->bClicked = false;
			}
			if (ButtonMap::GetMap()["LOAD"]->bClicked == true)
			{
				std::cout << "Load" << "\n";
				tileMap->LoadTileMap("TileTest.txt");
				ButtonMap::GetMap()["LOAD"]->bClicked = false;
			}
		});
	}
}

void TileMapSystem::AddTileOnClick(bool bHasCollision, ECS::ComponentHandle<TileMap> tileMap)
{
	/**
	Reference for window pointer that is used below to determine
	active cursor position for adding tiles
	*/
	sf::RenderWindow* _winRef = Engine::GetInstance().window;

	sf::Vector2f _mousePosView = _winRef->mapPixelToCoords(sf::Mouse::getPosition(*_winRef));

	sf::Vector2i _mousePosGrid(
		static_cast<int>(_mousePosView.x / tileMap->gridSizeF),
		static_cast<int>(_mousePosView.y / tileMap->gridSizeF));

	tileMap->AddTile(_mousePosGrid.x, _mousePosGrid.y, 0, bHasCollision);
}
