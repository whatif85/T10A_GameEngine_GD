#pragma once

#include <fstream>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "Engine.h"
#include "Tile.h"
#include "Interface/States.h"


struct Transform
{
public:
	ECS_DECLARE_TYPE;

	float xPos, yPos;
	float rotation;
	float xSpeed, ySpeed;
	float xSpeedMod, ySpeedMod;
	bool bColliding;

	Transform(float newX, float newY, float newXSpeed = 0.0f, float newYSpeed = 0.0f)
		: xPos(newX), yPos(newY), xSpeedMod(newXSpeed), ySpeedMod(newYSpeed)
	{
		this->rotation = 0.0f;
		this->xSpeed = 0.0f;
		this->ySpeed = 0.0f;
		this->bColliding = false;
	}

	void UpdateSpeed(float x, float y)
	{
		this->xSpeed = x;
		this->ySpeed = y;
	}

	void Move()
	{
		if (bColliding == false)
		{
			// halve the speed when moving diagonally
			if (xSpeed != 0 && ySpeed != 0)
			{
				xSpeed /= 2;
				ySpeed /= 2;
			}

			xPos += xSpeed;
			yPos += ySpeed;
		}
	}
};
ECS_DEFINE_TYPE(Transform);


struct Sprite2D
{
public:
	ECS_DECLARE_TYPE;

	sf::Sprite self;
	std::string filePath;
	int width, height;

	Sprite2D(std::string filePath)
	{
		this->filePath = filePath;
	}
};
ECS_DEFINE_TYPE(Sprite2D)


struct Animator
{
public:
	ECS_DECLARE_TYPE;

	int spriteWidth, spriteHeight;
	int currentColumn, currentRow;
	int totalColumns, totalRows;
	float currentTime, nextFrameTime;
	bool bFacingRight;

	Animator(int newWidth, int newHeight, float timeBetweenFrames, int columns, int rows) :
		spriteWidth(newWidth), spriteHeight(newHeight),
		nextFrameTime(timeBetweenFrames), totalColumns(columns), totalRows(rows)
	{
		currentColumn = 0;
		currentRow = 0;

		currentTime = 0;

		bFacingRight = true;
	}

	/*Animator(int newWidth, int newHeight, float timeBetweenFrames, int newColumns, int newRows)
	{
		this->spriteWidth = newWidth;
		this->spriteHeight = newHeight;

		currentColumn = 0;
		currentRow = 0;

		this->totalColumns = newColumns;
		this->totalRows = newRows;

		this->nextFrameTime = timeBetweenFrames;

		currentTime = 0;

		bFacingRight = true;
	}*/
};
ECS_DEFINE_TYPE(Animator);


struct InputController
{
public:
	ECS_DECLARE_TYPE;

	bool bInputActive;

	bool wKey, aKey, sKey, dKey;

	InputController()
	{
		bInputActive = true;

		wKey = false;
		aKey = false;
		sKey = false;
		dKey = false;
	}
};
ECS_DEFINE_TYPE(InputController);


struct BoxCollider
{
public:
	ECS_DECLARE_TYPE;

	// round up collision with tiles to avoid getting stuck
	int leftEdge, rightEdge, topEdge, bottomEdge;

	BoxCollider()
	{
		// set all structure's members to 0
		std::memset(this, '\0', sizeof(BoxCollider));
	}

	void Update(int xSide, int ySide, int width, int height)
	{
		leftEdge = xSide;
		rightEdge = xSide + width;
		topEdge = ySide;
		bottomEdge = ySide + height;
	}
};
ECS_DEFINE_TYPE(BoxCollider);


struct Tag
{
public:
	ECS_DECLARE_TYPE;

	std::vector<std::string> tagNames;

	Tag() = default;

	void AddTag(std::string tag)
	{
		tagNames.push_back(tag);
	}
};
ECS_DEFINE_TYPE(Tag);


struct TileMap
{
public:
	ECS_DECLARE_TYPE;

	float gridSizeF; // NOTE: Change this value to increase the size of the whole grid for more tile insertion

	uint32_t gridSizeU; // still unsigned int
	uint32_t layers; // The layer value used for rendering images in a certain order (see constructor)

	sf::Vector2u maxSize; // Vector to set the size of each tile
	sf::RectangleShape collisionBox; // The box outline of the tile which is rendered in RenderingSystem.cpp

	/**
		Map structure:
		1. Column of vectors
		2. Row of vectors
		3. Collection of tile pointers
	*/
	std::vector <std::vector<std::vector<Tile*>>> map; // vector in std is an "ArrayList" (not to be confused with math vector)

	TileMap()
	{
		this->gridSizeF = 50.0f;

		// return a value of new type, convert float to unsigned int
		//this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
		this->gridSizeU = static_cast<unsigned int>(this->gridSizeF);

		// number of tiles (size of tiles given by gridSize)
		this->maxSize.x = 20;
		this->maxSize.y = 20;

		this->layers = 1;

		this->map.resize(this->maxSize.x);

		for (size_t _x = 0; _x < this->maxSize.x; _x++)
		{
			this->map.push_back(std::vector<std::vector<Tile*>>());

			for (size_t _y = 0; _y < this->maxSize.y; _y++)
			{
				this->map[_x].resize(this->maxSize.y);
				this->map[_x].push_back(std::vector<Tile*>());

				for (size_t _z = 0; _z < this->layers; _z++)
				{
					this->map[_x][_y].resize(this->layers);
					this->map[_x][_y].push_back(nullptr);
				}
			}
		}

		this->collisionBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
		this->collisionBox.setFillColor(sf::Color(0, 255, 0, 50));
		this->collisionBox.setOutlineColor(sf::Color::Green);
		this->collisionBox.setOutlineThickness(-1.0f);
	}

	~TileMap()
	{
		Clear();
	}

	void AddTile(const uint32_t x, const uint32_t y, const uint32_t z, bool bHasCollision)
	{
		if (States::GetPausedState() == false)
		{
			printf("%d, %d, %d \n", maxSize.x, maxSize.y, layers);

			if (x < this->maxSize.x && x >= 0 &&
				y < this->maxSize.y && y >= 0 &&
				z < this->layers && z >= 0)
			{
				if (this->map[x][y][z] == nullptr) // if empty
				{
					this->map[x][y][z] = new Tile(x, y, this->gridSizeF, bHasCollision);
					std::cout << "Tile added" << std::endl;
				}
			}
		}
	}

	void Clear()
	{
		for (size_t _x = 0; _x < this->maxSize.x; _x++)
		{
			for (size_t _y = 0; _y < this->maxSize.y; _y++)
			{
				for (size_t _z = 0; _z < this->layers; _z++)
				{
					delete this->map[_x][_y][_z];
					this->map[_x][_y][_z] = NULL;
				}
				this->map[_x][_y].clear();
			}
			this->map[_x].clear();
		}
		this->map.clear();
	}

	void SaveTileMap(std::string fileName)
	{
		std::ofstream _saveFile;
		_saveFile.open(fileName);

		if (_saveFile.is_open() == true)
		{
			_saveFile << maxSize.x << " " << maxSize.y << "\n"
				<< gridSizeF << "\n"
				<< layers << "\n";

			for (size_t _x = 0; _x < this->maxSize.x; _x++)
			{
				for (size_t _y = 0; _y < this->maxSize.y; _y++)
				{
					for (size_t _z = 0; _z < this->layers; _z++)
					{
						if (this->map[_x][_y][_z] != nullptr)
						{
							_saveFile << _x << " " << _y << " " << _z << " " << this->map[_x][_y][_z]->ToString() << " " << "\n";
						}
					}
				}
			}
		}
		else
		{
			std::cerr << "Error: TileMap could not save to file " << fileName << "\n";
		}

		_saveFile.close();
	}

	void LoadTileMap(std::string filename)
	{
		std::printf("Loading TileMap\n");

		std::ifstream loadfile;
		loadfile.open(filename);

		if (loadfile.is_open() == true)
		{
			loadfile >> this->maxSize.x >> this->maxSize.y >> this->gridSizeF >> this->layers;
			this->gridSizeU = static_cast<uint32_t>(this->gridSizeF); // Return value of new type (float -> uint)

			Clear();

			this->map.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());

			for (size_t x = 0; x < this->maxSize.x; ++x)
			{
				for (size_t y = 0; y < this->maxSize.y; ++y)
				{
					this->map.at(x).resize(this->maxSize.y, std::vector<Tile*>());
					for (size_t z = 0; z < this->layers; ++z)
					{
						this->map.at(x).at(y).resize(this->layers, nullptr);
					}
				}
			}

			int _tX, _tY, _tZ;
			bool _bColliding = false;

			while (loadfile >> _tX >> _tY >> _tZ >> _bColliding)
			{
				printf("Read %d, %d, %d\n", _tX, _tY, _tZ);
				this->map.at(_tX).at(_tY).at(_tZ) = new Tile(_tX, _tY, this->gridSizeF, _bColliding);
			}
		}
		else
			std::cerr << "Error: TileMap could not load from file `" << filename << "'" << std::endl;
		loadfile.close();
	}
};
ECS_DEFINE_TYPE(TileMap);