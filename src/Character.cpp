#include "Character.h"

Character::Character():
	x(0), /* x position in the world */
	y(0), /* y position in the world */
	lastX(0),/* needed to be able to undo a move */
	lastY(0),/* needed to be able to undo a move */
	moveSpeed(0), /* running speed */
	width(0), /* bounding box width */
	height(0), /* bounding box height */
	velX(0), /* velocity in x-direction */
	velY(0), /* velocity in y-direction */
	gravity(2),
	sprite(),
	state(living) {
}

Character::~Character() {
}

void Character::init(string settings, string tag) {
	//load XML-parser
	ofxXmlSettings XML;

	if(!XML.loadFile(settings)) {
		cout << "Couldn't load Settings-File for " << tag << "!" << endl;
	}
	else {
		init(XML, tag);
	}
}

void Character::init(ofxXmlSettings& XML, string tag) {
	cout << "Processing Settings for " << tag << "!" << endl;
		
	x = XML.getValue("GAME:MAP:PLAYERS:" + tag + ":X", 0);
	y = XML.getValue("GAME:MAP:PLAYERS:" + tag + ":Y", 0);
	moveSpeed = XML.getValue("GAME:MAP:PLAYERS:" + tag + ":SPEED", 0);
	width = XML.getValue("GAME:MAP:PLAYERS:" + tag + ":WIDTH", 10);
	height = XML.getValue("GAME:MAP:PLAYERS:" + tag + ":HEIGHT", 10);

	// initialize with xml-file and name:
	sprite.init(XML, tag);

	timer = ofGetElapsedTimeMillis();

	derivedSetup();
}

void Character::derivedSetup() {
	/*does nothing in Character*/
}

void Character::bruise() {
	state = dying;
	timer = ofGetElapsedTimeMillis();
}

void Character::kill() {
	state = dead;
	timer = ofGetElapsedTimeMillis();
}

// draw the sprite (scaled):
void Character::draw(AssetManager* assets, float scaleFactorX,
				  float scaleFactorY) {
	sprite.draw(x, y, assets, scaleFactorX, scaleFactorY);
}

// check vertical line for collision:
bool Character::collision_ver(int x, int y, int& tilecoordx,
						   Map* map) {

	// calculate y tilecoords:
	int tileY = y - (y % map->getTileHeight());

	// calculate lowest point of the player:
	int bottom = y + height;

	// pixelcoords of the tile:
	tilecoordx = x / map->getTileWidth();
	int tilecoordy = tileY / map->getTileHeight();

	// check for collision:
	while(tileY <= bottom) {
		if(map->isSolid(tilecoordx, tilecoordy))
			return true;

		tilecoordy++;
		tileY += map->getTileHeight();
	}

	return false;
}

// check horizontal line for collision:
bool Character::collision_hor(int x, int y, int& tilecoordy,
						   Map* map) {

	// calculate x tilecoords:
	int tileX = x - (x % map->getTileWidth());

	// calculate rightmost point of the player:
	int right = x + width;

	// pixelcoords of the tile:
	tilecoordy = y / map->getTileHeight();
	int tilecoordx = tileX / map->getTileWidth();

	// check for collision:
	while(tileX <= right) {
		if(map->isSolid(tilecoordx, tilecoordy))
			return true;

		tilecoordx++;
		tileX += map->getTileWidth();
	}

	return false;
}

void Character::undoXMove() {
	x = lastX;
}

void Character::undoYMove() {
	y = lastY;
}

// getter/setter:
Status Character::getStatus() {
	return state;
}

int Character::getSpeed() {
	return moveSpeed;
}

int Character::getX() {
	return x;
}

int Character::getY() {
	return y;
}

void Character::setX(int val) {
	x = val;
}

void Character::setY(int val) {
	y = val;
}

int Character::getVelX() {
	return velX;
}

int Character::getVelY() {
	return velY;
}

float Character::getGravity() {
	return gravity;
}

int Character::getWidth() {
	return width;
}

int Character::getHeight() {
	return height;
}

int Character::getDeathTimer() {
	return ofGetElapsedTimeMillis() - timer;
}