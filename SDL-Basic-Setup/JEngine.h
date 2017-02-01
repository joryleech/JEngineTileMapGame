#ifndef JEngine_H
#define JEngine_H
#include <list>
#include <SDL.h>
#include <string>



class Color {
public:
	void setColor(Uint8, Uint8, Uint8, Uint8);
	Color();
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
	Color(Uint8, Uint8, Uint8, Uint8);
};
class Element
{
public:
	Element();
	bool hidden = false;

	virtual double getX();	double getY();	virtual void setX(double);	void setY(double); void hide(); void show(); bool isHidden();
	virtual void render() {};
	void moveBy(double x, double y);
	void moveTo(double x, double y);
	void rotateBy(double a);
	void rotateTo(double a);
	void flipHorizontal();
	void flipVertical();
	void setFlip(SDL_RendererFlip);
	int blitWidth, blitHeight;
protected:
	double x;
	double y;
	SDL_RendererFlip flipHoriz;
	SDL_RendererFlip flipVert;
	double angle;
	int imgwidth, imgheight;
};
class JBoundingBox {
public:


	JBoundingBox(double x, double y, int width,int height);
	bool isColliding(JBoundingBox* that);
	bool isColliding(int x, int y);
	bool isColliding(int x, int y, int width, int height);
	void resolveCollision(Element* link, JBoundingBox* that);
	void moveTo(double x, double y);
	double getX();
	double getY();
	int getWidth();
	int getHeight();
	void setX(double); void setY(double); void setWidth(int); void setHeight(int);
	JBoundingBox();
private:
	static double absoluteValue(double);
	static void findDifferenceForCollisions(JBoundingBox * s1, JBoundingBox * s2, double * toReturn);

	double x, y; int width, height;
};
class Image: public Element
{
public:
	bool isColliding(Image* e2);
	bool isCollidingAndAdjust(Image* e2);
	SDL_Texture* setImage(std::string);
	SDL_Texture * setImage(Image * x);
	SDL_Texture* setImage(std::string,int x, int y, int width,int height);
	void setBlit(int x, int y, int width, int height);
	Image();
	void render();
	Image(std::string url,int x,int y);
	Image(Image* url, int x, int y);
	~Image();
	void setScale(double); double getScale();
	double getWidth();
	double getHeight();
private:
	double scale=1;
	int iX, iY;
	SDL_Texture* image;bool imageOwned;
};

class Rect : public Element
{
public:
	SDL_Rect rect;
	Rect(double, double, int, int);
	Rect(double, double, int, int, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	Color setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 az);
	Color getColor();
	void render();
	int getWidth(); int getHeight();
	void setWidth(int); void setHeight(int);
private:
	int width;int height;
	Color color;
	
};
//TODO: Make JRenderer Class. A Renderable object that acts as a smaller screen inside a screen.
class JRenderer: public Element
{

};
class ImageManager
{
public:
	ImageManager();
	~ImageManager();
	Element* addElement(Element* i);
	void removeElement(Element* r);
	void removeAndDeleteElement(Element* r);
	void pushElementBack(Element* r);
	int pushToBack(Element* r);
	int pullToFront(Element* r);
	std::list<Element*>* getListPointer();
private:
	std::list<Element*>* ImageList;
	
};
class JInput
{
public:
	JInput();
	~JInput();
	void update();
	bool wasMouseClicked();
	bool wasMouseReleased();
	int getMouseXPos();
	int getMouseYPos();
	bool isKeyDown(int i);
	bool wasKeyPressed();
	bool wasKeyReleased();
	bool isMouseDown();

private:
	int timeout;
	int mouseX;
	bool mouseDown;
	bool mouseClicked;
	bool mouseReleased;
	SDL_Event event;
	int mouseY;
	const Uint8 *keyState;
};

class JEngine
{
public: 
	int init(std::string title, int widht,int height, int maxFrameRate);
	void setInputFrameIndependant(bool x);
	int init();
	void refreshScreen();
	SDL_Renderer* getRenderer();
	void paint();
	SDL_Window* getWindow();
	void setWindowFullScreen();
	int setMaxFrameRate(int x);
	ImageManager* getImageManager();
	ImageManager * getImageManager(ImageManager * i);
	Element* addElement(Element* e);
	Uint32 getTimeStep();
	JInput* getJInput();
	double getCameraX(); double getCameraY();
	void moveCameraTo(double x, double y);
	void moveCameraBy(double x, double y);
private:
	double cameraX=0;
	double cameraY=0;
	int maxFrameRate;
	ImageManager* imageManager;
	SDL_Window* window;
	SDL_Renderer* renderer;
	int width, height;
	std::string windowTitle;
	Uint32 lastUpdate;
	Uint32 timeBetweenFrames;
	Uint32 timeStep;
	Uint64 totalFrames;
	JInput* jInput;
	Uint32 timeLastPainted;
	bool frameIndependantInput;

};
class JTimer
{


};

#endif