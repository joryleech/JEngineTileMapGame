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
	std::vector<Tile> tiles; //TODO: Change to vector to support faster random access since size is constant on runtime
private:
	int tilesize;
	std::vector<ObjectID> tileMap;
	JRenderer * surface;
public:
	JRenderer * getSurface();
	Tilemap(int width,int height,int tilesize);
	void setMap(int newMap[]);
	~Tilemap();
	void renderMap();
	void renderTile(int x, int y, int tileID);
	Tile * getTile(int index);
	void setTile(int x, int y, int id);
	void setTile(int x, int y, int id, std::string info);
	std::string toString(bool);
	int coordToIndex(int x, int y);

};




#endif