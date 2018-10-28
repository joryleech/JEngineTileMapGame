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
	~Element() {};
	bool hidden = false;

	virtual double getX();	double getY();	virtual void setX(double);	void setY(double); void hide(); void show(); bool isHidden(); virtual double getScale();
	double getScaleX();
	double getScaleY();
	double getAngle();
	virtual void setScale(double scale);
	void setScale(double scaleX, double scaleY);
	virtual void render() {};
	void moveBy(double x, double y);
	void moveTo(double x, double y);
	void rotateBy(double a);
	void rotateTo(double a);
	void flipHorizontal();
	void flipVertical();
	void setFlip(SDL_RendererFlip);
	int blitWidth, blitHeight;
	void setBlendMode(SDL_BlendMode);
	SDL_BlendMode getBlendMode();
	std::string toString() {};
protected:
	SDL_BlendMode blendmode = SDL_BLENDMODE_BLEND;
	double x;
	double y;
	double scaleX = 1, scaleY = 1;
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
	static bool isPointInBox(double x, double y, SDL_Rect rect);
private:
	static double absoluteValue(double);
	static void findDifferenceForCollisions(JBoundingBox * s1, JBoundingBox * s2, double * toReturn);

	double x, y; int width, height;
};
class Text : public Element
{
public:
	Text(std::string text, float x, float y);
private:
	std::string text;
	Color color;
	SDL_Texture* texture;
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
	Image(Element * url, int x, int y, int width, int height);
	SDL_Texture * duplicateElement(Element * element, int width, int height);
	~Image();
	double getWidth();
	double getHeight();
private:
	int iX, iY;
	SDL_Texture* image;bool imageOwned;
};

class Rect : public Element
{
public:
	SDL_Rect rect;
	Rect(double, double, float, float);
	Rect(double, double, float, float, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	~Rect();
	Color setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	Color getColor();
	void render();
	float getWidth(); float getHeight();
	void setWidth(float); void setHeight(float);
	void setFilled(bool);
private:
	bool filled = true;
	float width;float height;
	Color color;
	
};
class ImageManager
{
public:
	ImageManager();
	~ImageManager();
	Element* addElement(Element* i);
	void removeElement(Element* r);
	void removeAndDeleteElement(Element* r);
	void removeAndDeleteAllElements();
	void removeAllElements();
	void pushElementBack(Element* r);
	int pushToBack(Element* r);
	int pullToFront(Element* r);
	std::list<Element*>* getListPointer();
private:
	std::list<Element*>* ImageList;

};
//TODO: Make JRenderer Class. A Renderable object that acts as a smaller screen inside a screen.
class JRenderer: public Element
{
public:
	JRenderer(double, double, int,int);
	~JRenderer();
	
	ImageManager * getImageManager();
	ImageManager * setImageManager(ImageManager * i);
	Element* addElement(Element* e);
	void renderElement(Element* e);
	void render();
	void forceClearTexture();
	void forceRenderTexture();
	void setWidth(int x); void setHeight(int y);
	int getWidth(); int getHeight();
	void setAutoRender(bool);
	SDL_Texture * getTexture();
private:
	bool autoRender = true;
	int width;
	int height;
	SDL_Texture * createRenderTexture();
	bool wasSizeChanged = false;
	ImageManager* imageManager;
	SDL_Texture * renderTexture;
};

class JInput
{
public:
	JInput();
	~JInput();
	void update();
	int getMouseXPosRaw();
	int getMouseYPosRaw();
	bool wasMouseClicked(int mouseButton);
	bool wasMouseReleased(int mouseButton);

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
	bool leftMouseClicked;
	bool leftMouseReleased;
	bool rightMouseClicked;
	bool rightMouseReleased;

	SDL_Event event;
	int mouseY;
	const Uint8 *keyState;
};

class JEngine
{
public: 
	~JEngine();
	int init(std::string title, int width,int height, int maxFrameRate);

	int init();
	void refreshScreen();
	SDL_Renderer* getRenderer();
	void paint();
	float getDeltaTime();
	SDL_Window* getWindow();
	void setWindowFullScreen();
	int setMaxFrameRate(int x);
	ImageManager* getImageManager();
	ImageManager * setImageManager(ImageManager * i);
	Element* addElement(Element* e);
	Uint32 getTimeStep();
	JInput* getJInput();
	bool getQuit();
	void quit();
	bool windowShutDown = false;
	int getWidth(); int getHeight();
	void debugPrint(std::string);
	float getScreenScaleX();
	float getScreenScaleY();
	float getResolutionX();
	float getResolutionY();
private:


	bool debug=true;
	int maxFrameRate;
	SDL_Window* window;
	SDL_Renderer* renderer;
	JRenderer* renderSurface;
	int resolutionWidth, resolutionHeight;
	int width, height;
	std::string windowTitle;
	Uint32 lastUpdate;
	Uint32 timeBetweenFrames;
	Uint32 timeStep;
	Uint64 totalFrames;
	JInput* jInput;
	Uint32 timeLastPainted;



};
class JTimer
{


};

#endif