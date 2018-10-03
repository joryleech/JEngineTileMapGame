#pragma once
#ifndef TilemapEditorH
#define TilemapEditorH
#include "Tilemap.h"
#include "gameController.h"
class TilemapEditor : GameController{
	TilemapEditor();
	virtual void update();
	virtual void onStart();
	virtual void onExit();
	virtual void load();
	virtual void postLoad();

};


#endif
