#include "JEngine.h"
#include <string>
#include <list>
#ifndef Tilemap
#define Tilemap


class Tile {
public:
	static enum CollisionBehavior {
		None = 0,
		Boundry = 1
	};
private:
	Element * image;
	CollisionBehavior collisionBehavior;
//Functions
public:
	Tile(std::string url, CollisionBehavior colBehavior);
	~Tile();
};

class objectID {
public:
    int tile;
	std::string info;
};

class tilemap{
public:
	static Tile debug;
	static Tile clear;
	std::list<Tile> tiles;
private:
	objectID** tileMap;
	JRenderer surface;

};




#endif