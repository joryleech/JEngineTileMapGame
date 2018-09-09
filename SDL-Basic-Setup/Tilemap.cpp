#include "Tilemap.h"

Tile::Tile(std::string url, CollisionBehavior colBehavior)
{
	this->image = new Image(url, 0, 0);
	this->collisionBehavior = colBehavior;
}
