/********************
*Filename: TestCode.cpp
*Author: Jory Leech
*Description: A test code that will change through out the project
*This code should probably be disregarded, as it is mostly used for testing
*Examples can be found in Examples.cpp

*********************/
#include <SDL.h>
#include <stdio.h>
#include <iostream>

#include "JEngine.h"



void createMap(JRenderer* map) {
	Color c[3];
	c[1].setColor(0, 0, 255, 255);
	c[2].setColor(0, 255, 255, 255);
	c[0].setColor(255, 0, 0, 255);
	int temp = 0;
	for (int x = 0;x < 64;x++) {
		for (int y = 0;y < 64;y++) {
			temp = ((x * y) % 3);
			map->addElement(new Rect(x, y, 1, 1, c[temp].r, c[temp].g, c[temp].b, c[temp].a));

		}
	}

}

int testCode(){
	JEngine* j;
	j = new JEngine();
	j->setInputFrameIndependant(false);
	j->init("Window", 640, 480, 60);
	j->setMaxFrameRate(-1);
	j->addElement(new Rect(0, 0, 640, 480, 0, 145, 0, 255));
	bool quit = 0;
	

	Rect * rect = new Rect(100, 100, 50, 30, 255, 0, 255, 120);
	

	JRenderer * renderer = new JRenderer(200, 200, 640, 480);
	j->addElement(renderer);
	Rect * rect2 = new Rect(100, 200, 50, 30, 255, 0, 255, 120);
	

	j->addElement(rect);
	renderer->addElement(rect);
	j->addElement(rect2);
	JRenderer* map[10][10];
	JBoundingBox* mapc[10][10];
	for (int x = 0;x < 10;x++){
		for (int y = 0;y < 10;y++) {
			map[x][y] = new JRenderer(x * 64, y * 64, 64, 64);
			j->addElement(map[x][y]);
			createMap(map[x][y]);
			//map[x][y]->hide();
			mapc[x][y] = new JBoundingBox(x * 64, y * 64, 64, 64);
			std::cout << "x:" << x <<" + y:" << y<<"\n" ;
			std::cout << map[x][y]->getImageManager()->getListPointer()->size();
		}

	}
	while (!quit) {
		if (j->getJInput()->isKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}
		for (int x = 0;x < 10;x++) {
			for (int y = 0;y < 10;y++) {
				map[x][y]->hide();
				if (mapc[x][y]->isColliding(j->getJInput()->getMouseXPos(), j->getJInput()->getMouseYPos())) {
					map[x][y]->show();
				}
			}
			
		}
		j->refreshScreen();
	}
	return 0;
}


