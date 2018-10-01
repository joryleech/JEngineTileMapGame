#include "Tilemap.h"
#include <iostream>
#include <list>
#include <sstream>
Element * Tile::getImage()
{
	return this->image;
}


Tile::Tile(std::string url)
{ 
	this->image = new Image(url, 0, 0);

}

Tile::Tile(int size ,Uint8 r,Uint8 g,Uint8 b,Uint8 a)
{
	this->image = new Rect(0,0,size,size,r,g,b,a);
	this->image->setBlendMode(SDL_BLENDMODE_BLEND);
}

Tile::~Tile()
{
	delete (this->image);
}

std::string Tile::toString()
{
	
	std::stringstream stringStream;
	const void* address = static_cast<const void*>(this);
	stringStream << "Tile::=" << address << ";ElementAddress:=" << static_cast<const void*>(this->image)<< "::\n";
	return stringStream.str();
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
	tiles.push_back(new Tile(32,255,0,255,0));
	//debug = Tile(tilesize,(Tile::CollisionBehavior)0, 255, 0, 255, 126);
	std::cout << "Tileset #"<<tiles.size();
}

void Tilemap::setMap(int newMap[])
{
	int x;
	int y;
	for (y = 0; y < (int)height;y++) {
		for (x = 0; x < (int)width;x++) {
			int index = coordToIndex(x, y);
			setTileRenderless(x, y, newMap[this->coordToIndex(x, y)]);
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
			setTileRenderless(currentX, currentY, newMap[currentNewIndex]);
		}
	}
	renderMap();
}


void Tilemap::renderMap() {
	if (!manualRender) {
		int x;
		int y;
		surface->forceClearTexture();
		for (y = 0; y < height; y++) {
			for (x = 0; x < width; x++) {
				renderTile(x, y, tileMap.at(coordToIndex(x, y)).tile);
			}
		}
	}
}

void Tilemap::forceRenderMap()
{
	bool tempManualRender = manualRender;
	manualRender = false;
	renderMap();
	manualRender = tempManualRender;

}

void Tilemap::renderTile(int x, int y, int tileID) {
	Element * tileToRender = this->getTileImage(tileID);
	tileToRender->moveTo(x*tilesize, y*tilesize);
	surface->renderElement(tileToRender);
	tileToRender->moveTo(0, 0);
}

void Tilemap::clearTile(int x, int y) {
	Element * tileToRender = clear.getImage();
	tileToRender->moveTo(x*tilesize, y*tilesize);
	surface->renderElement(tileToRender);
	tileToRender->moveTo(0, 0);
}



Element * Tilemap::getTileImage(int index) {
	if (index < 0 || index >= this->tiles.size()) {
		return (debug.getImage());
	}
	else {
		return (tiles[0]->getImage());
	}
	return (debug.getImage());
}
void Tilemap::setTile(int x, int y, int tileID) {
	setTile(x, y, tileID, "");
}
void Tilemap::setTile(int x, int y, int tileID,std::string info) {
	int index = coordToIndex(x, y);
	tileMap.at(index).tile = tileID;
	tileMap.at(index).info = info;
	clearTile(x, y);
	renderTile(x, y, tileID);
}
void Tilemap::setTileRenderless(int x, int y, int tileID, std::string info) {
	int index = coordToIndex(x, y);
	tileMap.at(index).tile = tileID;
	tileMap.at(index).info = info;
}
void Tilemap::setTileRenderless(int x, int y, int tileID) {
	setTileRenderless(x, y, tileID, "");
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

void Tilemap::setManualRender(bool manualRenderT)
{
	this->manualRender = manualRenderT;
}



