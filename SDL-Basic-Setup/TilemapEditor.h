#pragma once
#ifndef TilemapEditorH
#define TilemapEditorH
#include "Tilemap.h"
#include "gameController.h"
class TilemapEditor : GameController::GameState{
	TilemapEditor();
	void update();
	void onStart();
	void onExit();

};


#endif
