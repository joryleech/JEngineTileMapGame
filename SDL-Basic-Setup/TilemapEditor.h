#pragma once
#ifndef TilemapEditorH
#define TilemapEditorH
#include "Tilemap.h"
#include "gameController.h"
#include "Tilemap.h"
#include <functional>
class MenuButton {
public:
	Image * image;
	GameController::GameState * parent;
	JBoundingBox * boundingBox;
	void click();
	MenuButton(double x, double y, std::string imageURL, std::function<void()> click_func_ptr, std::function<void()> release_func_ptr, GameController::GameState * parent);
	void update();
	void release();
	static void blankFunction();
	~MenuButton();
	std::function<void()> click_func_ptr;
	std::function<void()> release_func_ptr;
};

class TilemapEditor : public GameController::GameState{
public:
	TilemapEditor(GameController * parent) : GameState(parent) {};
	void increaseTileID();
	void decreaseTileID();

	void update();
	void onStart();

	void onExit();
	void grab();
	void releaseGrab();
	~TilemapEditor();
	std::string tileMapToString(Tilemap *);
private:
	Tilemap * tileMap;

	int menuWidth = 400;
	int tileMapWidth = 20;
	int tileMapHeight = 20;
	
	//Functional Mouse Origin, is defined as the origin of the mouse position, for functions that depend on it changing.
	//When unused will remain -1
	int dragMouseOriginX = -1;
	int dragMouseOriginY = -1;
	double tilemapDragOriginX, tilemapDragOriginY;
	JBoundingBox * nonMenuSpace;
	//Menu
	Rect * menuBackground;
	
	MenuButton * leftTileSelectorButton;
	MenuButton * rightTileSelectorButton;

	//Tile Placement 
	int currentTileID = 3;
	Image * tileCursor;

};


#endif
