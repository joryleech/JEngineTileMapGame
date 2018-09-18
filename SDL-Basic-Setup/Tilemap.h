#pragma once
#include "JEngine.h"
#include <string>
#include <list>
#include <vector>
#ifndef TilemapH
#define TilemapH


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
	Element * getImage();
	Tile() : Tile("Resources/Images/debug.png", CollisionBehavior::Boundry) {};
	Tile(std::string url, CollisionBehavior colBehavior);
	Tile(int size, CollisionBehavior colBehavior, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	~Tile();
	int debug = 100;
	std::string toString();
};

class ObjectID {
public:
    int tile;
	std::string info;
public:
	ObjectID(int,std::string);
	ObjectID(int);
	ObjectID();
};


class Tilemap{
public:
	int height, width;
	Tile debug;
	Tile clear;
	std::vector<Tile*> tiles;
private:
	int tilesize;
	std::vector<ObjectID> tileMap;
	JRenderer * surface;
public:
	JRenderer * getSurface();
	Tilemap(int width,int height,int tilesize);
	void setMap(int newMap[]);
	void setPartialMap(int Map[], int destinationX, int destinationY, int partialWidth, int partialHeight);
	~Tilemap();
	void renderMap();
	void renderTile(int x, int y, int tileID);
	Element * getTileImage(int index);
	void setTile(int x, int y, int id);
	void setTile(int x, int y, int id, std::string info);
	std::string toString(bool);
	int coordToIndex(int x, int y);
	

};




#endif