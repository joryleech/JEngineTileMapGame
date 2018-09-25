#pragma once
#ifndef gameControllerH
#define gameControllerH
#include "JEngine.h"
#include <list>

static int engineScreenWidth=1920;
static int engineScreenHeight=1080;
class GameState {

public:
	static enum stateModificaction {
		None, Pop, Replace, Push, ReplaceAndDelete, PopAndDelete
	};

	stateModificaction modifyState = None;
	GameState * stateModificactionpointer = NULL;
	GameState();
	virtual void update() {};
	virtual void onStart() {};
	virtual void onExit() {};
	virtual void load() {};
	virtual void postLoad() {};
	JRenderer * getScreen();
	void createScreen(int width, int height);
protected:
	JRenderer * screen;
};

class GameController {
	std::list<GameState> gameStateStack;
	GameController(JEngine * engine);
	void update();
	~GameController();
	JEngine * engine;
	GameState * changeState(GameState * newState);
private:
	GameState * defaultState;
};
#endif
