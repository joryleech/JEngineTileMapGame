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
		static enum stateModificaction {
			None, Pop, Replace, Push, ReplaceAndDelete, PopAndDelete
		};

		stateModificaction modifyState = None;
		GameState * stateModificactionpointer = NULL;
		GameState(GameController * parent);
		/** Abstract Functions **/
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

	std::list<GameState *> gameStatesToDelete;
	std::list<GameState *> gameStateStack;
	GameController(JEngine * engine,GameState* defaultState);
	GameController(JEngine * engine) : GameController(engine, nullptr) {};
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
	GameState * getCurrentState();
private:
   void changeState(GameState * newState);

	GameState * defaultState;

};
#endif

class DefaultState : GameController::GameState {
	void onStart();
};