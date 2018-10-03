#include "TilemapEditor.h"
#include "JEngine.h"
#include <string>

void TilemapEditor::update()
{
	JInput * input = parent->engine->getJInput();

	smiley->moveTo(input->getMouseXPos(), 0);
	smiley->rotateBy(.2);
	if (parent->engine->getJInput()->isKeyDown(SDL_SCANCODE_F1)) {
		printf("%f\n", parent->engine->getDeltaTime());
	}
}

void TilemapEditor::onStart()
{
	smiley = new Image("Resources/Images/ImageExample1.png", 200, 200);
	this->getScreen()->addElement(smiley);
}

void TilemapEditor::onExit()
{

}
