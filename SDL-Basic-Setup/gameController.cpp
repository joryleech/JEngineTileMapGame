#include "gameController.h"

GameController::GameController(JEngine * engine)
{
	this->engine = engine;
}

void GameController::update()
{
	if (currentState != NULL) {
		currentState->update();
	}
	else if (defaultState != NULL) {
		this->changeState(defaultState);
	}
	else{
		engine->debugPrint("GameState is set to null");
	}
}

GameState * GameController::changeState(GameState * newState)
{
	currentState->onStart();

	this->engine->getImageManager()->removeElement(oldState->getScreen());
	this->engine->addElement(currentState->getScreen());

	return oldState;
}

JRenderer * GameState::getScreen()
{
	return this->screen;
}

void GameState::createScreen(int width, int height)
{
	this->screen = new JRenderer(0, 0, width, height);
}
