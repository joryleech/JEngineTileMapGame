#include "TilemapEditor.h"
#include "JEngine.h"
#include <string>
#include <windows.h>
#include <stdio.h>
#include <iostream>
void TilemapEditor::update()
{
	JInput * input = parent->engine->getJInput();
	tileCursor->moveTo(input->getMouseXPos()-(this->tileMap->getTileSize()/2), input->getMouseYPos() - (this->tileMap->getTileSize() / 2));
	tileCursor->duplicateElement(tileMap->getTileImage(currentTileID), this->tileMap->getTileSize(), this->tileMap->getTileSize());
	if (parent->engine->getJInput()->isKeyDown(SDL_SCANCODE_F1)) {
		printf("%f\n", parent->engine->getDeltaTime());
	}



	//Menu Interaction
	leftTileSelectorButton->update();



	



	//Non-Menu Mouse Interaction
	if (input->isKeyDown(SDL_SCANCODE_C))
	{
		this->parent->engine->debugPrint("exporting");

	}

	if (nonMenuSpace->isColliding(input->getMouseXPos(), input->getMouseYPos())) {
		//Grab function, moves the tilemap equal to the ammount moved while 
		if (input->isKeyDown(SDL_SCANCODE_SPACE)) {
			this->grab();
		}
		if (!input->isKeyDown(SDL_SCANCODE_SPACE)) {
			this->releaseGrab();
			if (input->isMouseDown()) {
				int gridX = (int)(input->getMouseXPos() - tileMap->getSurface()->getX())/32;
				int gridY = (int)(input->getMouseYPos() - tileMap->getSurface()->getY())/32;

				this->tileMap->setTile(gridX, gridY, currentTileID);
			}
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
	this->tileMap->createTileSet("Resources/Images/testTileSet.png");
	int x[] =
	{
		1,2,3,4,
		23,24,24,25,
		33,34,34,35,
		-1,-1,23,-1

	};

	this->tileMap->setPartialMap(x, 0, 0, 4, 4);

	this->getScreen()->addElement(tileMap->getSurface());
	//Changing Tile
	this->tileCursor = new Image("Resources/Images/testTileSet.png", 100, 100);
	this->screen->addElement(tileCursor);

	nonMenuSpace = new JBoundingBox(0, 0, this->screen->getWidth() - menuWidth, this->screen->getHeight());
	//Create Menu Items
	this->screen->addElement(new Rect(this->screen->getWidth() - menuWidth - 5, 0, 5, this->screen->getHeight(),0,0,0,20));
	this->menuBackground = new Rect(this->screen->getWidth() - menuWidth, 0, menuWidth, this->screen->getHeight(),255,255,255, 255);
	this->getScreen()->addElement(menuBackground);
	
	this->leftTileSelectorButton = new MenuButton(this->screen->getWidth() - menuWidth, (double)100, "Resources/Images/TileMapEditor/menuLeftButton.png", MenuButton::blankFunction, MenuButton::blankFunction, (GameState*)this);


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


MenuButton::MenuButton(double x, double y, std::string imageURL, void (*click_func_ptr)(), void (*release_func_ptr)(),GameController::GameState * parent)
{
	this->image = new Image(imageURL, x, y);
	
	this->boundingBox = new JBoundingBox(x, y, image->getWidth(), image->getHeight());

	this->click_func_ptr = click_func_ptr;
	this->release_func_ptr = release_func_ptr;
	this->parent = parent;
	this->parent->getScreen()->addElement(this->image);
}

void MenuButton::update() {
	JInput * input = parent->parent->engine->getJInput();
	float mouseX, mouseY;
	mouseX = input->getMouseXPos();
	mouseY = input->getMouseYPos();

	if (this->boundingBox->isColliding(mouseX,mouseY)) {
		if (input->wasMouseClicked(0)) {
			click();
		}
		if (input->wasMouseReleased(0)) {
			release();
		}
	}
}
void MenuButton::click()
{
	if (this->click_func_ptr != nullptr) {
		click_func_ptr();
	}
}


void MenuButton::release()
{
	if (this->release_func_ptr != nullptr) {
		release_func_ptr();
	}

}

void MenuButton::blankFunction()
{

}

MenuButton::~MenuButton()
{
	this->parent->getScreen()->getImageManager()->removeAndDeleteElement(this->image);
	delete(image);
	delete(boundingBox);
}
