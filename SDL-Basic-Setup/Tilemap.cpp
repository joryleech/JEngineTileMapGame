#include "Tilemap.h"
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <fstream>
#include "pugixml.hpp" as pugi
Element * Tile::getImage()
{
	return this->image;
}


Tile::Tile(std::string url)
{ 
	this->image = new Image(url, 0, 0);
	this->image->setBlendMode(SDL_BLENDMODE_BLEND);
}

Tile::Tile(int size ,Uint8 r,Uint8 g,Uint8 b,Uint8 a)
{
	this->image = new Rect(0,0,size,size,r,g,b,a);
	this->image->setBlendMode(SDL_BLENDMODE_NONE);
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

int Tilemap::getTileSize()
{
	return tilesize;
}

JRenderer * Tilemap::getSurface()
{
	return surface;
}

Tilemap::Tilemap(int width, int height,int tilesize)
{
	this->clear.getImage()->setBlendMode(SDL_BLENDMODE_NONE);
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
		return (tiles[index]->getImage());
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

int Tilemap::createTileSet(std::string url)
{
	int startingIndex= (this->tiles.size());
	Image * currentTileSet = new Image(url, 0, 0);
	int tilesPerLine = (int)(currentTileSet->getWidth() / this->tilesize);
	int linesOfTiles = (int)(currentTileSet->getHeight() / this->tilesize);
		for (int y = 0; y < linesOfTiles; y++) {
			for (int x = 0; x < tilesPerLine; x++)
			{
				tiles.push_back(new TileSetTile(currentTileSet, x, y,this->tilesize));
			}
		}


	return startingIndex;
}

Element * TileSetTile::getImage()
{
	Image * imageTemp = (Image*)this->image; //This does not create a new instance, Temp image is only used to reference Image only functions to the element.
	imageTemp->setBlit(this->tileSetX*this->tileSize, this->tileSetY*this->tileSize, tileSize, tileSize);
	return imageTemp;
}


TileSetTile::TileSetTile(Image * image, int x, int y, int tileSize) {
	this->image = image;
	this->tileSetX = x;
	this->tileSetY = y;
	this->tileSize = tileSize;
}


TileSetTile::TileSetTile(std::string url, int x, int y, int tileSize) {
	this->image = new Image(url, 0, 0);
	this->tileSetX = x;
	this->tileSetY = y;
	this->tileSize = tileSize;
}

bool Tilemap::exportToFile(std::string url) {
	return this->exportToFile("map", url);
}

bool Tilemap::exportToFile(std::string mapName, std::string url) {
		pugi::xml_document xmlDocument;
		pugi::xml_node node = xmlDocument.append_child("Layer1");
		exportToXMLNode("Layer1",node);
		pugi::xml_document temp;
		temp.append_child("Destory");




		std::ofstream file;
		file.open(url+mapName+".xml");
		xmlDocument.print(file);
		file.close();
		


		return true;
}



std::vector<std::string> Tilemap::getParseableItemsFromString(std::string mapText) {
	int currentCharIndex = 0;
	std::vector<char> level;
	std::vector<std::string> toReturn;
	std::stringstream currentString;
	while (currentCharIndex < mapText.length()) {
		char currentChar = mapText.at(currentCharIndex);
		if (level.size()<1) {

		}
		if (currentChar == '\\' && currentCharIndex <= mapText.length() - 2) {
			//If escape character is called ignore it
			currentCharIndex += 2;
			continue;
		}
		if (currentChar == '[') {
			level.push_back('[');
		}


	}
	return toReturn;
}

void Tilemap::exportToXMLNode(std::string layerName, pugi::xml_node& layer) {
	pugi::xml_node simpleTiles = layer.append_child("simpleTiles");
	layer.append_attribute("width") = this->width;
	layer.append_attribute("height") = this->height;
	simpleTiles.append_attribute("data") = this->generateSimpleTiles().c_str();
	pugi::xml_node complexTiles = layer.append_child("complexTiles");
	generateComplexTiles(complexTiles);

}

void Tilemap::generateComplexTiles(pugi::xml_node& node) {
	for (int i = 0; i < this->tileMap.size(); i++) {
		if (tileMap.at(i).info.length() > 0) {
			std::string name= "Tile" + i;
			pugi::xml_node currentNode = node.append_child("TILE");
			currentNode.append_attribute("index") = i;
			currentNode.append_attribute("data") = tileMap.at(i).info.c_str();
		}
	}
 
}

std::string Tilemap::generateSimpleTiles() {
	std::stringstream mapStream;
	for (int tile = 0; tile < this->tileMap.size(); tile++) {
		std::stringstream tileStream;
		ObjectID currentTile = tileMap.at(tile);
		tileStream << (&currentTile)->tile;
		if (tile + 1 < tileMap.size()) {
			tileStream << ",";
		}
		mapStream << tileStream.str();
	}
	return mapStream.str();
}

std::string Tilemap::toString() {
	std::stringstream mapStream;
	for (int tile = 0; tile < this->tileMap.size(); tile++) {
		std::stringstream tileStream;
		ObjectID currentTile = tileMap.at(tile);
		tileStream << "" << (&currentTile)->tile;
		if (!currentTile.info.length()<1) {
			tileStream << ":\"" << (&currentTile)->info <<"\"";
		}
		mapStream << tileStream.str();
	}
	return mapStream.str();
}

