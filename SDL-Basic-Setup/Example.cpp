/******************************
*Filename: Example.cpp
*Author: Jory Leech
*Description: Various examples of how to use JEngine.
*Run any of these in the main method. 
*Warning: Use only one method per program, this is due to the way JEngine is controlled. 
******************************/
#include "JEngine.h";
/********************
*Name: ImageExample
*Params: None
*Description: An example of how to load an image using JEngine
*Notes: None
********************/
void ImageExample()
{
	JEngine * engine = new JEngine();
	//Required to initilize the window. 
	engine->init("Image Example", 640, 480, 60);
	engine->setMaxFrameRate(60);
	//Creates a pointer to an image, and fills it with an image from the url at the position.
	Image * image = new Image("Resources/Images/ImageExample1.png", 200, 200);
	//This adds the image to the rendering list. Without this you own the image but it will not draw to the screen.
	engine->addElement(image);
	//getQuit is an important method and the only way to check if the x button was clicked. 
	while (!engine->getQuit())
	{
		engine->refreshScreen();
	}
	delete(engine);
}
/********************
*Name: InputExample
*Params: None
*Description: An example of how to use keyboard input to move an object using JEngine
*Notes: None
********************/
void InputExample()
{
	JEngine * engine = new JEngine();
	engine->init("Image Example", 640, 480, 60);
	engine->setMaxFrameRate(60);
	int speed = 200;
	Image * image = new Image("Resources/Images/ImageExample1.png", 200, 200);
	engine->addElement(image);
	JInput * inputController = engine->getJInput();
	while (!engine->getQuit())
	{
		if (inputController->isKeyDown(SDL_SCANCODE_W)) {
			image->moveBy(0, -speed);
		}
		if (inputController->isKeyDown(SDL_SCANCODE_A)) {
			image->moveBy(-speed, 0);
		}
		if (inputController->isKeyDown(SDL_SCANCODE_S)) {
			image->moveBy(0,speed);
		}
		if (inputController->isKeyDown(SDL_SCANCODE_D)) {
			image->moveBy(speed,0);
		}

		engine->refreshScreen();
	}
	delete(engine);
}

int main(int argc, char* args[])
{
	InputExample();
	return 0;
}