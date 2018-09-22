#include "JEngine.h"
#include <SDL.h>
#include <string>
#include <iostream>
#include <SDL_image.h>
JEngine* windowAndRenderer = NULL;
/**
*Color



**/
Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}
Color::Color()
{
	Color(0xFF, 0x00, 0xFF, 0xFF);
}
void Color::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

/**



Element

**/
Element::Element() {
	int x = 0;
	int y = 0;
	flipHoriz = SDL_FLIP_NONE;
	angle = 0;
	this->setBlendMode(SDL_BLENDMODE_BLEND);
}
double Element::getX() {
	return this->x;
}
double Element::getY() {
	return this->y;
}
void Element::hide() {
	this->hidden = true;
}
void Element::show() {
	this->hidden = false;
}
void Element::setX(double newx)
{
	this->x = newx;
}
void Element::setY(double newY)
{
	this->y = newY;
}
bool Element::isHidden() {
	return (this->hidden);
}
void Element::setScale(double scale)
{
	this->scale = scale;
}
double Element::getScale()
{
	return this->scale;
}
void Element::moveBy(double x2, double y2)
{
	this->x += (x2*windowAndRenderer->getTimeStep() / 1000.f);
	this->y += (y2*windowAndRenderer->getTimeStep() / 1000.f);
}
void Element::moveTo(double x2, double y2)
{
	this->x = x2;
	this->y = y2;
}

void Element::rotateBy(double a)
{
	this->angle += (a*windowAndRenderer->getTimeStep() / 1000.f);
	if (angle > 360) {
		angle -= 360;
	}
	if (angle < 0) {
		angle += 360;
	}
}

void Element::rotateTo(double a)
{
	a = fmod(a, 360);
	this->angle = a;
}

void Element::flipHorizontal()
{
	if (this->flipHoriz = SDL_FLIP_HORIZONTAL) {
		this->flipHoriz = SDL_FLIP_NONE;
	}
	else {
		this->flipHoriz = SDL_FLIP_HORIZONTAL;
	}
}
void Element::flipVertical()
{
	if (this->flipVert = SDL_FLIP_VERTICAL) {
		this->flipVert = SDL_FLIP_NONE;
	}
	else {
		this->flipVert = SDL_FLIP_VERTICAL;
	}
}

void Element::setFlip(SDL_RendererFlip x)
{
	if (x & SDL_FLIP_HORIZONTAL) {
		flipHoriz = SDL_FLIP_HORIZONTAL;
	}
	else {
		flipHoriz = SDL_FLIP_NONE;
	}
	if (x & SDL_FLIP_VERTICAL) {
		flipVert = SDL_FLIP_VERTICAL;
	}
	else {
		flipVert = SDL_FLIP_NONE;
	}
}

void Element::setBlendMode(SDL_BlendMode newBlendMode)
{
	this->blendmode = newBlendMode;
}
SDL_BlendMode Element::getBlendMode() {
	return (this->blendmode);
}





Image::Image(std::string url, int x, int y) {
	this->x = x;
	this->y = y;
	this->setImage(url);
	scale = 1;
	iX = 0;iY = 0;blitWidth = 0;blitHeight = 0;
}
Image::Image(Image* img, int x, int y) {
	this->x = x;
	this->y = y;
	
	std::cout << "imgPointed:" << img->image << "\n";
	this->setImage(img);
	scale = 1;
	iX = 0;iY = 0;blitWidth = 0;blitHeight = 0;
}
double Image::getWidth()
{
	if (blitWidth==0) {
		return imgwidth*scale;
	}
	else { return blitWidth*scale; }
}
double Image::getHeight()
{
	if (blitHeight==0) {
		return imgheight*scale;
	}
	else { return blitHeight*scale; }
}
bool Image::isColliding(Image* e2)
{
	JBoundingBox s1, s2;
	s1.setX((this->getX()));s1.setY(this->y);s1.setWidth(this->getWidth());s1.setHeight(this->getHeight());
	s2.setX((e2->getX()));s2.setY(e2->y);s2.setWidth(e2->getWidth());s2.setHeight(e2->getHeight());
	return (s1.isColliding(&s2));
}
bool Image::isCollidingAndAdjust(Image * e2)
{
	JBoundingBox s1, s2;
	s1.setX((this->getX()));s1.setY(this->getY());s1.setWidth(this->getWidth());s1.setHeight(this->getHeight());
	s2.setX((e2->getX()));s2.setY(e2->getY());s2.setWidth(e2->getWidth());s2.setHeight(e2->getHeight());
	if (s1.isColliding(&s2))
	{
		s1.resolveCollision(this, &s2);
		return true;
	}
	return false;
}
SDL_Texture* Image::setImage(std::string url)
{
	if (imageOwned &&(this->image != NULL || this->image != nullptr)) {
		SDL_DestroyTexture(this->image);
		image = NULL;
	}
	imageOwned = true;
	SDL_Surface* tempSurface = IMG_Load(url.c_str());
	if (tempSurface == NULL) {
		printf("Unable To Load Image: %s : SDL Error:%s", url.c_str(), SDL_GetError());
	}
	else {
		this->image = SDL_CreateTextureFromSurface(windowAndRenderer->getRenderer(), tempSurface);
		if (this->image == NULL) {
			printf("Unable To Create Texture: %s : SDL Error:%s", url.c_str(), SDL_GetError());
		}
		this->imgwidth = tempSurface->w;
		this->imgheight = tempSurface->h;
		SDL_FreeSurface(tempSurface);
	}
	return this->image;
}
SDL_Texture* Image::setImage(Image* x) {
	if (imageOwned && (this->image != NULL || this->image != nullptr)) {
		SDL_DestroyTexture(this->image);
		image = NULL;
	}
	imageOwned = false;
	this->imgwidth = x->imgwidth;
	this->imgheight = x->imgheight;
	this->image = x->image;
	return this->image;
}
void Image::setBlit(int x2, int y2, int width2, int height2) {
	iX = x2;iY = y2;blitWidth = width2; blitHeight = height2;
}
Image::~Image() {
	if (imageOwned && image != nullptr) {
		SDL_DestroyTexture(this->image);
	}
	image = nullptr;
}
void Image::render()
{
	if (this->image == NULL) {
	}
	else if (iX == 0 && iY == 0 && blitWidth == 0 && blitHeight == 0) {
		SDL_Rect dest = { std::round(this->x),std::round(this->y), this->imgwidth*scale, this->imgheight*scale };
		SDL_RenderCopyEx(windowAndRenderer->getRenderer(), this->image, NULL, &dest,this->angle,NULL, (SDL_RendererFlip)(flipHoriz | flipVert));
	}
	else {
		SDL_Rect blit = { iX,iY,blitWidth,blitHeight };
		SDL_Rect dest = { (int)std::round(this->x) ,(int)std::round(this->y), this->blitWidth*scale, this->blitHeight*scale };
		SDL_RenderCopyEx(windowAndRenderer->getRenderer(), this->image, &blit, &dest, this->angle, NULL, (SDL_RendererFlip)(flipHoriz | flipVert));
	}
}

Rect::Rect(double x2, double y2, float width, float height, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	Element();
	this->setX(x2);
	this->y = y2;
	this->width = width;this->height = height;
	color.setColor(r, g, b, a);

}

Rect::~Rect()
{
}

Rect::Rect(double x2, double y2, float width2, float height2) {
	Rect(x2, y2, width2, height2, 0xFF, 0x00, 0xFF, 0xFF);

}
void Rect::render()
{
	rect = { (int)std::round(this->x),(int)std::round(this->y),(int)std::round(this->width*((int)scale)),(int)std::round(this->height*((int)scale)) };

	SDL_SetRenderDrawColor(windowAndRenderer->getRenderer(), color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(windowAndRenderer->getRenderer(), &rect);
}

float Rect::getWidth()
{
	return this->width;
}

float Rect::getHeight()
{
	return this->height;
}

void Rect::setWidth(float x)
{
	this->width = x;
}

void Rect::setHeight(float x)
{
	this->height = x;
}

JRenderer::JRenderer(double x, double y, int width, int height)
{
	this->x = x; this->y = y;
	this->width = width; this->height = height;
	this->renderTexture = this->createRenderTexture();
	this->imageManager = new ImageManager();
}
JRenderer::~JRenderer() {
	this->imageManager->removeAndDeleteAllElements();
	if (this->imageManager != nullptr) {
		delete(this->imageManager);this->imageManager = nullptr;
	}
	if (this->renderTexture != nullptr) {
		SDL_DestroyTexture(this->renderTexture);
		this->renderTexture = nullptr;
	}
	SDL_SetTextureBlendMode(renderTexture, SDL_BLENDMODE_BLEND);
}
ImageManager * JRenderer::getImageManager()
{
	return this->imageManager;
}
Element * JRenderer::addElement(Element * e)
{
	this->getImageManager()->addElement(e);
	return e;
}

void JRenderer::renderElement(Element * e)
{
	SDL_SetRenderTarget(windowAndRenderer->getRenderer(), this->renderTexture);
	SDL_SetTextureBlendMode(this->renderTexture, (e)->getBlendMode());

	(e)->render();
	//Reseting the Render target is essential after rendering, otherwise the texture will not complete rendering.
	SDL_SetRenderTarget(windowAndRenderer->getRenderer(), NULL ); //Do not remove.
}

void JRenderer::forceRenderTexture() {
	if (this->wasSizeChanged) {
		this->createRenderTexture();
		wasSizeChanged = false;
	}
	std::list<Element*>::iterator it;
	std::list<Element*>::iterator itEnd = this->imageManager->getListPointer()->end();
	SDL_SetRenderTarget(windowAndRenderer->getRenderer(), this->renderTexture);
	SDL_SetRenderDrawColor(windowAndRenderer->getRenderer(), 0, 0, 0, 0);
	SDL_SetTextureBlendMode(this->renderTexture, SDL_BLENDMODE_BLEND);

	SDL_RenderClear(windowAndRenderer->getRenderer());
	for (it = this->imageManager->getListPointer()->begin(); it != itEnd; ++it)
	{
		if (!(*it)->isHidden()) {
			SDL_SetTextureBlendMode(this->renderTexture, (*it)->getBlendMode());
			(*it)->render();
		}
	}
}
void JRenderer::render() {
	if (this->wasSizeChanged) {
		this->createRenderTexture();
		wasSizeChanged = false;
	}
	if (autoRender) {
		this->forceRenderTexture();
	}
	SDL_SetRenderTarget(windowAndRenderer->getRenderer(), NULL);
	SDL_Rect dest = { (int)std::round(this->x),(int)std::round(this->y),((int)this->width*scale), ((int) this->height*scale) };
	SDL_RenderCopyEx(windowAndRenderer->getRenderer(), this->renderTexture, NULL, &dest, this->angle, NULL, (SDL_RendererFlip)(flipHoriz | flipVert));
}
void JRenderer::forceClearTexture()
{
	SDL_SetRenderTarget(windowAndRenderer->getRenderer(), this->renderTexture);
	SDL_SetRenderDrawColor(windowAndRenderer->getRenderer(), 0, 0, 0, 0);

	SDL_RenderClear(windowAndRenderer->getRenderer());
}
SDL_Texture * JRenderer::createRenderTexture()
{
	if (this->renderTexture != nullptr) {
		SDL_DestroyTexture(this->renderTexture);
		this->renderTexture = nullptr;
	}
	SDL_SetRenderDrawColor(windowAndRenderer->getRenderer(), 0, 0, 0, 0);
	this->renderTexture=SDL_CreateTexture(windowAndRenderer->getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, this->width, this->height);
	if (this->renderTexture == nullptr) {
		std::cout << "Unable to create renderer texture";
	}
	return this->renderTexture;
}
void JRenderer::setWidth(int x)
{
	this->width = x;
	this->wasSizeChanged = true;
}

void JRenderer::setHeight(int y)
{
	this->height = y;
	this->wasSizeChanged = true;
}

void JRenderer::setAutoRender(bool t)
{
	this->autoRender = t;
}




/*








*/
ImageManager::ImageManager()
{
	this->ImageList = new std::list<Element*>();
}
ImageManager::~ImageManager()
{
	delete(this->ImageList);
}
Element* ImageManager::addElement(Element* i) {
	this->ImageList->emplace_back(i);
	return i;
}
void ImageManager::removeElement(Element * r)
{
	this->ImageList->remove(r);
}
void ImageManager::removeAndDeleteElement(Element * r)
{
	this->ImageList->remove(r);
	delete(r);
}
void ImageManager::removeAndDeleteAllElements()
{
	while (!this->ImageList->empty()) {
		delete(this->ImageList->front());
		this->ImageList->pop_front();
	}
}
void ImageManager::pushElementBack(Element * r)
{
	this->ImageList->push_back(r);
}
std::list<Element*>* ImageManager::getListPointer()
{
	return this->ImageList;
}


/**
Name: Init
Description: Initilizes the window to a 640x480 pixel screen that is not limited in its frame rate
	Refer to init later to find full details. 
**/
int JEngine::init() {
	return init("Test Window", 640, 480, 0);
}
JEngine::~JEngine()
{
	//Todo Check this deletes everything.

	if (this->imageManager != nullptr) {
		delete(imageManager);
		imageManager = nullptr;
	}
	delete(jInput);
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);

	windowAndRenderer = NULL;
}
/**
Name: Init
Description: Initilizes the window to a 640x480 pixel screen that is not limited in its frame rate
Refer to init later to find full details.
**/
int JEngine::init(std::string title, int width, int height, int maxFrameRate) {
	//Initializes all of the functions of SDL
	//TODO: Optimize for necessities.
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("JEngine Window Could Not Be Created\n SDL Error: %s\n", SDL_GetError());
		return -1;
	}
	if (windowAndRenderer == NULL) {
		SDL_ShowCursor(SDL_ENABLE);
		windowAndRenderer = this;
		this->width = width;this->height = height; this->windowTitle = title; this->setMaxFrameRate(maxFrameRate);
		this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, SDL_WINDOW_SHOWN);
		this->imageManager = new ImageManager();
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}
		if (this->window == NULL) {
			printf("JEngine Window Could Not Be Created\n SDL Error: %s\n", SDL_GetError());
			return -1;
		}
		this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
		if (this->renderer == 0) {
			printf("JEngine Renderer Could Not Be Created\n SDL Error: %s\n", SDL_GetError());
			return -1;
		}
		SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		lastUpdate = SDL_GetTicks();
		this->jInput = new JInput();
		this->frameIndependantInput = false;
	}
	return 0;
}
void JEngine::refreshScreen()
{
	if (windowAndRenderer != nullptr) {
		this->paint();
		this->jInput->update();
	}

}
void JEngine::setInputFrameIndependant(bool x)
{
	frameIndependantInput = x;
}
void JEngine::paint() {

	Uint32 currentTicks = SDL_GetTicks();
	Uint32 oTimeStep;
	bool return2 = false;
	if (frameIndependantInput) {
	//This version should not be default.
	//This works by returning to the game loop instead of rendering if the frame rate sleep is not met
	//More resource intensive. 
	//Doesn't appear to make a difference.
		if (this->maxFrameRate > 0) {
			Uint32 timeSincePaint = currentTicks - timeLastPainted;
			if (timeSincePaint < this->timeBetweenFrames) {
				SDL_Delay(1);
				return2 = true;//SDL_Delay(timeBetweenFrames - (oTimeStep));
			}

		}
		timeStep = SDL_GetTicks() - lastUpdate;
		if (timeStep < 1) {
			SDL_Delay(1);
			timeStep = 1;
		}
		lastUpdate = SDL_GetTicks();

		if (return2) { return; }
	}
	else {
		//a negative framerate indicates no max frame rate.
		if (this->maxFrameRate >= 0) {
			oTimeStep = currentTicks - lastUpdate;
			if (oTimeStep < this->timeBetweenFrames) {
				SDL_Delay(timeBetweenFrames - (oTimeStep));
			}
		}
		timeStep = SDL_GetTicks() - lastUpdate;
		if (timeStep < 1) {
			SDL_Delay(1);
			timeStep = 1;
		}
		lastUpdate = currentTicks;
	}

	SDL_RenderClear(renderer);

	//this->imageManager->getListPointer()->begin();
	std::list<Element*>::iterator it;
	std::list<Element*>::iterator itEnd = imageManager->getListPointer()->end();
	for (it = this->imageManager->getListPointer()->begin();
		it != itEnd;
		++it)
	{
		if (!(*it)->isHidden()) {
			SDL_SetRenderDrawBlendMode(this->renderer, (*it)->getBlendMode());
			(*it)->render();
		}
	}
	

	SDL_RenderPresent(this->renderer);
	timeLastPainted = SDL_GetTicks();

	SDL_SetRenderDrawColor(windowAndRenderer->getRenderer(), 0x00, 0x01, 0x10, 0xFF);
	totalFrames++;


}
SDL_Window* JEngine::getWindow()
{
	return this->window;
}
ImageManager* JEngine::getImageManager() {
	return imageManager;
}
ImageManager* JEngine::setImageManager(ImageManager* i) {
	ImageManager* x = this->getImageManager();
	this->imageManager = i;
	return x;
}
Element * JEngine::addElement(Element * e)
{
	this->getImageManager()->addElement(e);
	return e;
}
Uint32 JEngine::getTimeStep()
{
	return timeStep;
}
JInput * JEngine::getJInput()
{
	return this->jInput;
}
bool JEngine::getQuit()
{
	return this->windowShutDown;
}
void JEngine::debugPrint(std::string print)
{
	if (debug) {
		std::cout << print;
	}
}
SDL_Renderer* JEngine::getRenderer()
{
	return this->renderer;
}
void JEngine::setWindowFullScreen() {
	SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN_DESKTOP);

}

int JEngine::setMaxFrameRate(int x)
{
	this->maxFrameRate = x;
	if (x > 0) {
		timeBetweenFrames = 1000 / (x);
	}
	else {

	}
	return x;
}

JInput::JInput()
{
	this->keyState = SDL_GetKeyboardState(NULL);
}
JInput::~JInput()
{

}
void JInput::update() {

	if (SDL_PollEvent(&event) != 0) {
		if (event.type == SDL_QUIT) {
			windowAndRenderer->windowShutDown = true;
		}
		if (event.type == SDL_MOUSEMOTION)
		{
			SDL_GetMouseState(&mouseX, &mouseY);
		}
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			this->mouseDown = true;
		}
		if (event.type == SDL_MOUSEBUTTONUP)
		{
			this->mouseDown = false;
		}
	
	}

}
int JInput::getMouseXPos() {
	int x; int y;
	SDL_GetMouseState(&x, &y);
	return x;
}
int JInput::getMouseYPos() {
	int x; int y;
	SDL_GetMouseState(&x, &y);
	return y;
}
bool JInput::isKeyDown(int i)
{
	if (i < 0) {
		return false;
		std::cout << "Unable to process input request";

	}
	else {
		return this->keyState[i];
	}
}

bool JInput::isMouseDown()
{
	return mouseDown;
}

JBoundingBox::JBoundingBox(double x2, double y2, int width2, int height2)
{
	this->x = x2;
	this->y = y2;
	this->width = width2;
	this->height = height2;
}
bool JBoundingBox::isColliding(JBoundingBox* that)
{
	if (this->x + this->width < that->x || this->x > that->x + that->width) return false;
	if (this->y + this->height < that->y || this->y >that->y + that->width) return false;
	return true;
}
bool JBoundingBox::isColliding(int x, int y)
{
	//Todo: Fix this with actual point containing algorithm
	JBoundingBox* temp = new JBoundingBox(x, y, 1, 1);
	bool temp2= this->isColliding(temp);
	delete(temp);
	return temp2;
}
void JBoundingBox::resolveCollision(Element* link, JBoundingBox* that)
{
	double changes[] = { 0,0 };
	findDifferenceForCollisions(this, that,changes);
	this->x += changes[0];
	this->y += changes[1];
	if (link != nullptr) {
		link->moveTo(link->getX() + changes[0], link->getY() + changes[1]);
	}
}
void JBoundingBox::moveTo(double x, double y) {
	this->x = x;
	this->y = y;
}
double JBoundingBox::getX() {
	return this->x;
}
double JBoundingBox::getY() {
	return this->y;
}

int JBoundingBox::getWidth()
{
	return this->width;
}

int JBoundingBox::getHeight()
{
	return height;
}

void JBoundingBox::setX(double x)
{
	this->x = x;
}
void JBoundingBox::setY(double y)
{
	this->y = y;
}
void JBoundingBox::setWidth(int i)
{
	this->width = i;
}
void JBoundingBox::setHeight(int i)
{
	this->height = i;
}
JBoundingBox::JBoundingBox()
{

}
double JBoundingBox::absoluteValue(double x)
{
	if (x < 0) {
		return (-1 * x);
	}
	return x;
}

void JBoundingBox::findDifferenceForCollisions(JBoundingBox * s1, JBoundingBox * s2, double* toReturn)
{
	double xDif = 0;
	double yDif = 0;
	if (s1->getX() + (s1->getWidth()) > s2->getX() + (s2->getWidth() ))
	{
		xDif = s2->getX() + (s2->getWidth()) - (s1->getX());
	}
	else {
		xDif = (s2->getX()) - (s1->getX() + (s1->getWidth()));
	}

	if (s1->getY() > s2->getY())
	{
		yDif = s2->getY() + (s2->getHeight()) - (s1->getY());
	}
	else {
		yDif = s2->getY() - (s1->getY() + (s1->getHeight()));
	}
	if (absoluteValue(xDif) > absoluteValue(yDif)) {
		toReturn[1] = yDif;
	}
	else {
		toReturn[0] = xDif;
	}
}

