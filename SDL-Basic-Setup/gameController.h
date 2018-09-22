#pragma once
#include "JEngine.h"
int screenWidth = 640;
int screenHeight = 480;

class GameState {

public:
	virtual void update() {};
	virtual void onStart() {};
	virtual void onExit() {};
	virtual void load() {};
	virtual void postLoad() {};
	JRenderer * getScreen();
protected:
	JRenderer * screen;
};

class GameController {
	GameController(JEngine * engine);
	void update();
	~GameController();

	JEngine * engine;
	GameState * changeState(GameState * newState);
private:
	GameState * currentState;
	GameState * defaultState;
};

