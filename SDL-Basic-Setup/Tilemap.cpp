#include "Tilemap.h"
#include <iostream>
#include <list>
Element * Tile::getImage()
{
	return this->image;
}


Tile::Tile(std::string url, CollisionBehavior colBehavior)
{ 
	this->image = new Image(url, 0, 0);
	this->collisionBehavior = colBehavior;
}

Tile::Tile(int size, CollisionBehavior colBehavior,Uint8 r,Uint8 g,Uint8 b,Uint8 a)
{
	this->image = new Rect(0,0,size,size,r,g,b,a);
	this->collisionBehavior = colBehavior;
}

Tile::~Tile()
{
	delete (this->image);
}

std::string Tile::toString()
{
	return "";
}

ObjectID::ObjectID(int id, std::string info)
{
	this->tile = id;
	this->info = info;
}

ObjectID::ObjectID(int id)
{
	ObjectID(id, "");
}

ObjectID::ObjectID()
{
	ObjectID(0);
}

JRenderer * Tilemap::getSurface()
{
	return surface;
}

Tilemap::Tilemap(int width, int height,int tilesize)
{

	this->tilesize = tilesize;
	this->width = width;
	this->height = height;
	this->surface = new JRenderer(0, 0, width*tilesize, height*tilesize);
	for (int i = 0; i < width*height; i++) {
		tileMap.push_back(ObjectID(0,""));
	}
	this->surface->setAutoRender(false);
	this->surface->forceClearTexture();
	surface->forceRenderTexture();
	tiles.push_back(Tile(32, Tile::CollisionBehavior::Boundry, 0, 0, 255, 126));
	//debug = Tile(tilesize,(Tile::CollisionBehavior)0, 255, 0, 255, 126);
	
}

void Tilemap::setMap(int newMap[])
{
	int x;
	int y;
	for (y = 0; y < (int)height;y++) {
		for (x = 0; x < (int)width;x++) {
			int index = coordToIndex(x, y);
			setTile(x, y, newMap[this->coordToIndex(x, y)]);
		}
	}
	this->renderMap();
}
void Tilemap::setPartialMap(int newMap[], int destinationX, int destinationY, int partialWidth, int partialHeight) {
	int iteratorX, iteratorY;
	for (iteratorY = 0; iteratorY < partialHeight; iteratorY++) {
		for (iteratorX = 0; iteratorX < partialWidth; iteratorX++) {
			int currentX = iteratorX + destinationX;
			int currentY = iteratorY + destinationY;
			int currentNewIndex = iteratorX + (iteratorY*partialWidth);
			setTile(currentX, currentY, newMap[currentNewIndex]);
		}
	}
	renderMap();
}


void Tilemap::renderMap() {
	int x;
	int y;
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			renderTile(x, y, tileMap.at(coordToIndex(x, y)).tile);
		}
	}

}

void Tilemap::renderTile(int x, int y, int tileID) {
	Tile * tileToRender = this->getTile(tileID);
	Element * toRender = tileToRender->getImage();
	toRender->moveTo(x*tilesize, y*tilesize);
	surface->renderElement(toRender);
	toRender->moveTo(0, 0);
}

Tile * Tilemap::getTile(int index) {
	if (index < 0 || index >= this->tiles.size()) {
		return &(this->debug);
	}
	else {
		return &(tiles.at(index));
	}

}

void Tilemap::setTile(int x, int y, int tileID) {
	setTile(x, y, tileID, "");
}
void Tilemap::setTile(int x, int y, int tileID,std::string info) {
	int index = coordToIndex(x, y);
	tileMap.at(index).tile = tileID;
	tileMap.at(index).info = info;
}
std::string Tilemap::toString(bool)
{
	std::string toReturn = "";
	int y;
	int x;
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {

			toReturn += "[";
			toReturn+=std::to_string(tileMap[coordToIndex(x, y)].tile);
			toReturn += ":";
			toReturn += tileMap[coordToIndex(x, y)].info;
			toReturn += "]";
		}
		toReturn += "\n";
	}
	return toReturn;
}


int Tilemap::coordToIndex(int x, int y) {
	return ((y*this->width) + x);
}



