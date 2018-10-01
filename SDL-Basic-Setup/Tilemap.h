#pragma once
#include "JEngine.h"
#include <string>
#include <list>
#include <vector>
#ifndef TilemapH
#define TilemapH


class Tile {
public:
private:
	Element * image;
//Functions
public:
	Element * getImage();
	Tile() : Tile("Resources/Images/debug.png") {};
	Tile(std::string url);
	Tile(int size, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
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
	Tile clear = Tile(32, 255, 0, 255, 0);
	std::vector<Tile*> tiles;
private:
	int tilesize;
	std::vector<ObjectID> tileMap;
	JRenderer * surface;
	bool manualRender = false;
public:
	JRenderer * getSurface();
	Tilemap(int width,int height,int tilesize);
	void setMap(int newMap[]);
	void setPartialMap(int Map[], int destinationX, int destinationY, int partialWidth, int partialHeight);
	~Tilemap();
	void forceRenderMap();
	void renderTile(int x, int y, int tileID);
	void clearTile(int x, int y);
	Element * getTileImage(int index);
	void setTile(int x, int y, int id);
	void setTile(int x, int y, int id, std::string info);
	void setTileRenderless(int x, int y, int tileID, std::string info);
	void setTileRenderless(int x, int y, int tileID);
	std::string toString(bool);
	int coordToIndex(int x, int y);
	void setManualRender(bool);
private:
	void renderMap();

};




#endif