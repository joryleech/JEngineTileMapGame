#include "TilemapEditor.h"
#include "JEngine.h"
#include <string>

void TilemapEditor::update()
{
	JInput * input = parent->engine->getJInput();

	if (parent->engine->getJInput()->isKeyDown(SDL_SCANCODE_F1)) {
		printf("%f\n", parent->engine->getDeltaTime());
	}

	//Non-Menu Mouse Interaction
	if (nonMenuSpace->isColliding(input->getMouseXPos(), input->getMouseYPos())) {
		//Grab function, moves the tilemap equal to the ammount moved while 
		if (input->isKeyDown(SDL_SCANCODE_SPACE)) {
			this->grab();
		}
		if (!input->isKeyDown(SDL_SCANCODE_SPACE)) {
			this->releaseGrab();
		}
		
		
		




	}
}


void TilemapEditor::onStart()
{
	Rect * background = new Rect(0, 0, screen->getWidth(), screen->getHeight(), 224, 224, 224, 255);
	screen->addElement(background);
	//Create Tilemap items
	this->tileMap = new Tilemap(500, 200, 32);
	Image * image2 = new Image("Resources/Images/ImageExample1.png", 200, 200);
	int x[] =
	{
		-1,-1,0,-1,
		-1,-1,0,0,
		-1,-1,0,0,
		-1,-1,0,-1

	};
	for (int i = 0; i < 2; i++) {
		this->tileMap->setPartialMap(x, i, 0, 4, 4);
	}
	this->getScreen()->addElement(tileMap->getSurface());



	nonMenuSpace = new JBoundingBox(0, 0, this->screen->getWidth() - menuWidth, this->screen->getHeight());
	//Create Menu Items
	this->screen->addElement(new Rect(this->screen->getWidth() - menuWidth - 5, 0, 5, this->screen->getHeight(),0,0,0,20));
	this->menuBackground = new Rect(this->screen->getWidth() - menuWidth, 0, menuWidth, this->screen->getHeight(),255,255,255, 255);
	this->getScreen()->addElement(menuBackground);
	
}

void TilemapEditor::onExit()
{

}

void TilemapEditor::grab() {
	JInput * input = this->parent->engine->getJInput();
	int mouseXMoved = 0;
	int mouseYMoved = 0;
	//If the origin has not been set by the function yet.
	if (dragMouseOriginX < 0) {
		dragMouseOriginX = input->getMouseXPos();
		dragMouseOriginY = input->getMouseYPos();
		tilemapDragOriginX = tileMap->getSurface()->getX();
		tilemapDragOriginY = tileMap->getSurface()->getY();
	}
	else {
		mouseXMoved = input->getMouseXPos() - dragMouseOriginX;
		mouseYMoved = input->getMouseYPos() - dragMouseOriginY;
		tileMap->getSurface()->moveTo(tilemapDragOriginX + mouseXMoved, tilemapDragOriginY + mouseYMoved);
	}
}
void TilemapEditor::releaseGrab() {
	dragMouseOriginX = -1;
	dragMouseOriginY = -1;
	tilemapDragOriginX = -1;
	tilemapDragOriginY = -1;
}


MenuButton::MenuButton(double x, double y, std::string imageURL, void (*click_func_ptr)(), void (*release_func_ptr)())
{
	this->image = new Image(imageURL, x, y);
	
	this->boundingBox = new JBoundingBox(x, y, image->getWidth(), image->getHeight());

	this->click_func_ptr = click_func_ptr;
	this->release_func_ptr = release_func_ptr;

}
void MenuButton::click()
{
	click_func_ptr();
}


void MenuButton::release()
{
	release_func_ptr();
}

MenuButton::~MenuButton()
{
	delete(image);
	delete(boundingBox);
}
