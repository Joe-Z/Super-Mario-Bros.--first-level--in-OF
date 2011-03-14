#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

// supported spritesheets are:
// images that have the same width and height for every sprite.
// images that consist of 4 rows, from the top: up, right, down, left.
// the number of columns has to be same in every row.

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "AssetManager.h"

struct PixelRGBA {
	unsigned char r, g, b, a;
};

// direction in which the character faces:
enum Directions {leftDir, rightDir};

class SpriteSheet {
public:
	SpriteSheet();
	void init(string settings, string tag);
	void init(ofxXmlSettings& XML, string tag);
	~SpriteSheet();
	void move(bool left, bool right, bool lockjump);
	void killPic(int row, int col);
	void draw(float xPos, float yPos, AssetManager* assets,
			  float scaleFactorX = 1, float scaleFactorY = 1);

private:
	string imagePath;
	Directions direction;
	bool moving;
	int timer, animLength;
	int currentSlice[2];
	int maxRows, maxCols;
	int stepWidth, stepHeight;
	int idleCol;
};

#endif //SPRITE_H_INCLUDED