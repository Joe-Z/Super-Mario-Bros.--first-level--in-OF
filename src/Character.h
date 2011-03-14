#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include "ofMain.h"
#include "SpriteSheet.h"
#include "AssetManager.h"
#include "Map.h"

enum Status {living, dying, dead};

class Character {
public:
	Character();

	virtual ~Character();

	// every Character-subclass needs an init-function
	virtual void init(string settings, string tag);
	virtual void init(ofxXmlSettings& XML, string tag);

	//makes you dying
	virtual void bruise();
	//makes you dead
	virtual void kill();

	// draw Character with adjustable scale-factors:
	void draw(AssetManager* assets,
			  float scaleFactorX = 1,
			  float scaleFactorY = 1);

	Status getStatus();

	void undoXMove();
	void undoYMove();

	int getX();
	int getY();

	void setX(int val);
	void setY(int val);

	int getVelX();
	int getVelY();

	float getGravity();

	int getSpeed();
	int getWidth();
	int getHeight();

	int getDeathTimer();

protected:
	//a setup-function called within init()
	//allowing derived classes to set their
	//variables without having to override init()
	virtual void derivedSetup();

	// check vertical line for collision:
	bool collision_ver(int x, int y, int& tilecoordy,
					   Map* map);
	// check horizontal line for collision:
	bool collision_hor(int x, int y, int& tilecoordy,
					   Map* map);

	Status state;

	// x, y = world-coordinates
	int x, y;
	int lastX, lastY;
	float velX, velY;
	float gravity;
	int moveSpeed; // running speed.

	int width, height;
	SpriteSheet sprite;
	int timer; // used for time-based calculations.
};


#endif // CHARACTER_H_INCLUDED
