#pragma once

#include <sstream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class Tile
{
public:
	bool bColliding;
	sf::RectangleShape shape;

	Tile();
	Tile(float xPos, float yPos, float gridSizeF, bool bColliding);
	~Tile();

	void Render(sf::RenderTarget& target);
	const bool& GetCollision() const; // cannot modify values when calling
	const sf::Vector2f& GetPosition() const;
	std::string ToString();
};

