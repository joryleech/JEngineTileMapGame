#include "gameController.h"

GameController::GameController(JEngine * engine,GameState * defaultState)
{
	this->defaultState = defaultState;
	this->engine = engine;
}

void GameController::update()
{
	if (!gameStateStack.empty() && defaultState!=nullptr) {
		
	}
	else if (defaultState != NULL) {
		this->pushState(defaultState);
	}
	else{
		engine->debugPrint("GameState is set to null");
	}
}


GameState * GameController::changeState(GameState * newState)
{
	//The Engine must remove the render texture of other screens, inorder to render this screen.
	this->engine->getImageManager()->removeAllElements();
	this->engine->addElement(getCurrentState()->getScreen());

	//TODO: Remove return
	return nullptr;
	//return oldState;
}
GameState * GameController::getCurrentState() {
	if (gameStateStack.empty()) {
		return nullptr;
	}
	return gameStateStack.back;
}

JRenderer * GameState::getScreen()
{
	return this->screen;
}

void GameState::createScreen(int width, int height)
{
	this->screen = new JRenderer(0, 0, width, height);
}
