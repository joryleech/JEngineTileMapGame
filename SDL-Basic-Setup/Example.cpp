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
	bool keepRunning = true;
	//Creates a pointer to an image, and fills it with an image from the url at the position.
	Image * image = new Image("Resources/Images/ImageExample1.png", 200, 200);
	//This adds the image to the rendering list. Without this you own the image but it will not draw to the screen.
	engine->addElement(image);
	while (keepRunning)
	{
		engine->refreshScreen();
	}
	
}

int main(int argc, char* args[])
{
	ImageExample();
	return 0;
}