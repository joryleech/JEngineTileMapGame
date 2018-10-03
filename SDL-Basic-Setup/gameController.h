#pragma once
#ifndef gameControllerH
#define gameControllerH
#include "JEngine.h"
#include <list>


class GameController {
public:
	class GameState {
	public:
		GameController * parent;
		GameState * stateModificactionpointer = NULL;
		explicit GameState(GameController * parent);
		JRenderer * getScreen();
		void createScreen(int width, int height);
	protected:
		JRenderer * screen;

	public:
		/** Abstract Functions **/
		virtual void update() {};
		virtual void onStart() {};
		virtual void onExit() {};
	};

	std::list<GameState *> gameStatesToDelete;
	std::list<GameState *> gameStateStack;
	GameController(JEngine * engine,GameState* defaultState);
	GameController(JEngine * engine) : GameController(engine, NULL) {};
	void update();
	~GameController();
	JEngine * engine;
	
	GameState * popState();
	std::list<GameState *> popState(int count);
	GameState * replaceState(GameState * newState);
	void pushState(GameState * newState);
	void replaceAndDeleteState(GameState * newState);
	void popAndDeleteState();
	void deleteState(GameState * state);
	bool stateChanged = false;
private:
   void changeState(GameState * newState);
   GameState * getCurrentState();
   GameState * defaultState;

};
#endif

class DefaultState : GameController::GameState {
public:
	DefaultState(GameController * parent) : GameState(parent) {};
	void update();
	void onStart();
	void onExit();


};