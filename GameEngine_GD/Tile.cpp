#include "Tile.h"


Tile::Tile() = default;

Tile::Tile(float xPos, float yPos, float gridSizeF, bool bColliding)
{
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(sf::Color::Red);
	this->shape.setPosition(xPos * gridSizeF, yPos * gridSizeF);

	this->bColliding = bColliding;
}

Tile::~Tile() = default;

void Tile::Render(sf::RenderTarget & target)
{
	target.draw(this->shape);
}

const bool& Tile::GetCollision() const
{
	return this->bColliding;
}

const sf::Vector2f& Tile::GetPosition() const
{
	return this->shape.getPosition();
}

std::string Tile::ToString()
{
	std::stringstream _stringForm;
	_stringForm << this->bColliding << " ";

	return _stringForm.str();
}
