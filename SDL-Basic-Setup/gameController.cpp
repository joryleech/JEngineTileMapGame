#include "gameController.h"

GameController::GameController(JEngine * engine,GameController::GameState * defaultState)
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
		engine->debugPrint("GameController::GameState is set to null");
	}
}

GameController::GameState * GameController::popState()
{
	GameController::GameState* oldState = this->gameStateStack.back();
	this->gameStateStack.pop_back(); //Unlike standard pop this does not return the object
	changeState(this->getCurrentState());
	return oldState;
}
std::list<GameController::GameState*> GameController::popState(int count)
{
	std::list<GameController::GameState*> statesToReturn;
	for (int i = 0; i < count && !gameStateStack.empty(); i++) {
		statesToReturn.push_back(this->gameStateStack.back());
		this->gameStateStack.pop_back();
	}
	changeState(this->getCurrentState());
	return statesToReturn;
}

GameController::GameState * GameController::replaceState(GameController::GameState * newState)
{
	GameController::GameState* oldState = this->gameStateStack.back();
	this->gameStateStack.pop_back();
	this->pushState(newState);
	return oldState;
}

void GameController::pushState(GameController::GameState * newState)
{
	this->gameStateStack.push_back(newState);
	changeState(getCurrentState());
}


void GameController::changeState(GameController::GameState * newState)
{
	//The Engine must remove the render texture of other screens, inorder to render this screen.
	this->engine->getImageManager()->removeAllElements();
	this->engine->addElement(getCurrentState()->getScreen());


}
GameController::GameState * GameController::getCurrentState() {
	if (gameStateStack.empty()) {
		return nullptr;
	}
	return gameStateStack.back();
}

JRenderer * GameController::GameState::getScreen()
{
	return this->screen;
}

void GameController::GameState::createScreen(int width, int height)
{
	this->screen = new JRenderer(0, 0, width, height);
}

void DefaultState::onStart()
{
	
}
