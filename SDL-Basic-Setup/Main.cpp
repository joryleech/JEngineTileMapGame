#include <SDL.h>
#include <stdio.h>
#include <iostream>

#include "JEngine.h"

JEngine* j;
int main(int argc, char* args[])
{
	
	j = new JEngine(); 
	j->setInputFrameIndependant(true);
	j->init("Window",1920,1080,60);
	j->setMaxFrameRate(144);
	j->setWindowFullScreen();
	bool quit = 0;
	JRenderer * renderer = new JRenderer(200, 200, 640, 480);
	j->addElement(renderer);
	Rect * rect = new Rect(100, 100, 50, 30,255,0,255,120);
	Rect * rect2 = new Rect(100, 200, 50, 30, 255, 0, 255, 120);
	j->addElement(rect);
	renderer->addElement(rect);
	renderer->addElement(rect2);
	while (!quit) {
		if (j->getJInput()->isKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;


		}
		if (j->getJInput()->isKeyDown(SDL_SCANCODE_D))
		{
			rect->moveBy(200, 0);

		}
		rect2->moveBy(200, 0);
		j->refreshScreen();
	}
	return 0;
}

