#pragma once
#ifndef TilemapEditorH
#define TilemapEditorH
#include "Tilemap.h"
#include "gameController.h"
class TilemapEditor : public GameController::GameState{
public:
	TilemapEditor(GameController * parent) : GameState(parent) {};
	void update();
	void onStart();
	void onExit();
	~TilemapEditor();
private:
	Image * smiley;
};


#endif
