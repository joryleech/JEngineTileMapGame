#pragma once
#include "JEngine.h"
#include <string>
#include <list>
#include <vector>
#include "pugixml.hpp" as pugi
#ifndef TilemapH
#define TilemapH


class Tile {
public:
	virtual Element * getImage();
	Tile() : Tile("Resources/Images/debug.png") {};
	Tile(std::string url);
	Tile(int size, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	~Tile();
protected:
	Element * image;
//Functions
public:

	int debug = 100;
	std::string toString();
};
class TileSetTile :public Tile {
public:
	int tileSetX;
	int tileSetY;
	int tileSize;
	TileSetTile(std::string url, int x, int y, int tileSize);
	std::string toString();
	TileSetTile(Image *, int x, int y, int tileSize);
	Element * getImage() ;
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
	Tile clear = Tile(32, 255, 0, 255, 12);
	std::vector<Tile*> tiles;
private:
	int tilesize;
	std::vector<ObjectID> tileMap;
	JRenderer * surface;
	bool manualRender = false;
public:
	int getTileSize();
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
	int createTileSet(std::string);
	bool exportToFile(std::string url);
	bool exportToFile(std::string mapName, std::string url);
	std::vector<std::string> getParseableItemsFromString(std::string mapText);
	void exportToXMLNode(std::string layerName, pugi::xml_node & layer);
	void generateComplexTiles(pugi::xml_node & layer);
	std::string generateSimpleTiles();
	std::string toString();
private:
	void renderMap();

};




#endif