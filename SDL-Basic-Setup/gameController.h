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
	GameController(JEngine * engine,GameState* defaultState);
	GameController(JEngine * engine) : GameController(engine, nullptr) {};
	void update();
	~GameController();
	JEngine * engine;
	
	GameState * popState();
	GameState * replaceState(GameState * newState);
	void pushState(GameState * newState);
	void deleteState(GameState * state);
	GameState * getCurrentState();
private:
	GameState * changeState(GameState * newState);

	GameState * defaultState;
};
#endif
