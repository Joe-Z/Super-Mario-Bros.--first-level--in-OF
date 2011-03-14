#include "SpriteSheet.h"

SpriteSheet::SpriteSheet():
	maxRows(0), /* how many rows does the stilesheet have */
	maxCols(0), /* and how many columns */
	stepWidth(0), /* width of a single sprite */
	stepHeight(0), /* height of a single sprite */
	idleCol(0) { /* which column is the idle state */
}

void SpriteSheet::init(ofxXmlSettings& XML, string tag) {
	cout << "Processing SpriteSheet for " << tag << "!" << endl;

	imagePath = XML.getValue("GAME:MAP:PLAYERS:" + tag + ":SPRITESHEET", "");
	animLength = XML.getValue("GAME:MAP:PLAYERS:" + tag + ":ANIMLENGTH", 500);
	idleCol = XML.getValue("GAME:MAP:PLAYERS:" + tag + ":IDLECOL", 0);
	maxRows = XML.getValue("GAME:MAP:PLAYERS:" + tag + ":ROWS", 0);
	maxCols = XML.getValue("GAME:MAP:PLAYERS:" + tag + ":COLUMNS", 0);
	stepWidth = XML.getValue("GAME:MAP:PLAYERS:" + tag + ":WIDTH", 0);
	stepHeight = XML.getValue("GAME:MAP:PLAYERS:" + tag + ":HEIGHT", 0);

	// default sprite:
	currentSlice[1] = idleCol;
	currentSlice[0] = 2;

	direction = rightDir;
	timer = ofGetElapsedTimeMillis();
}

void SpriteSheet::init(string settings, string tag) {
	// load XML-parser:
	ofxXmlSettings XML;

	// load settings from the xml-file:
	if(!XML.loadFile(settings)) {
		cout << "Couldn't load Settings-File for " << tag << "!" << endl;
	}
	else {
		init(XML, tag);
	}
}

SpriteSheet::~SpriteSheet() {
}

void SpriteSheet::move(bool left, bool right, bool lockjump) {

	moving = true;

	// check if moving left, right or not moving:
	if(left)
		direction = leftDir;
	else if(right)
		direction = rightDir;
	else if(!left && !right)
		moving = false;

	switch(direction) {
	case leftDir:
		// facing left. not jumping:
		if(!lockjump) {
			currentSlice[0] = 3;
		}
		// facing left. jumping:
		else {
			currentSlice[0] = 2;
			currentSlice[1] = 2;
		}
		break;
	case rightDir:
		// facing right. not jumping:
		if(!lockjump) {
			currentSlice[0] = 1;
		}
		// facing right. jumping:
		else {
			currentSlice[0] = 0;
			currentSlice[1] = 1;
		}
		break;
	}

	//standing still
	if(!moving && !lockjump) {
		if(direction == leftDir)
			currentSlice[0] = 3;
		else if(direction == rightDir)
			currentSlice[0] = 1;

		currentSlice[1] = idleCol;
		timer = ofGetElapsedTimeMillis();
	}

	// time-based animation:
	if(moving &&
	   ofGetElapsedTimeMillis() - timer >= animLength / maxCols) {

		timer = ofGetElapsedTimeMillis();

		if(currentSlice[1] >= maxCols) {
			currentSlice[1] = 0;
		}
		else
			currentSlice[1]++;
	}
}

void SpriteSheet::killPic(int row, int col) {
	//row
	currentSlice[0] = row;
	//col
	currentSlice[1] = col;
}

void SpriteSheet::draw(float xPos, float yPos, AssetManager* assets,
					   float scaleFactorX, float scaleFactorY) {

	// get the spritesheet from the asset manager:
	ofImage* image = assets->getImage(imagePath, CHARACTER);
	PixelRGBA* imagePixels = (PixelRGBA*)image->getPixels();

	PixelRGBA* currentPixels = new PixelRGBA[stepWidth * stepHeight];

	// copy the pixels of the current sprite into currentPixels:
	int i = 0;
	for(int y = currentSlice[0] * stepHeight;
			y < currentSlice[0] * stepHeight + stepHeight;
			y++) {
		for(int x = y * image->getWidth() + (currentSlice[1] * stepWidth);
				x < y * image->getWidth() + (currentSlice[1] * stepWidth) + stepWidth;
				x++) {
			currentPixels[i].r = imagePixels[x].r;
			currentPixels[i].g = imagePixels[x].g;
			currentPixels[i].b = imagePixels[x].b;
			currentPixels[i].a = imagePixels[x].a;
			i++;
		}
	}

	ofImage slice;
	// copy the pixel to an ofImage for easy drawing:
	slice.setFromPixels((unsigned char*)currentPixels,
						stepWidth, stepHeight,
						OF_IMAGE_COLOR_ALPHA,
						true);

	ofEnableAlphaBlending();

	// draw the slice of the spritesheet scaled accordingly:
	slice.draw(xPos, yPos, stepWidth * scaleFactorX, stepHeight * scaleFactorY);

	ofDisableAlphaBlending();

	// cleanup:
	delete currentPixels;
}