#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "j.h"
#include "JEngine.h"


int main(int argc, char* args[])
{
	
	//JEngine* j = new JEngine();
	j = new JEngine(); 
	j->setInputFrameIndependant(true);
	j->init("Window",1920,1080,60);
	j->setMaxFrameRate(60);
	j->setWindowFullScreen();
	bool quit = 0;
	while (!quit) {
		if (j->getJInput()->isKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;

		}

		j->refreshScreen();
	}
	return 0;
}

