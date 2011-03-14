#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <vector>
#include <string>
#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "AssetManager.h"
#include "Tile.h"

class Map {
public:
	Map();
	void initMap(string settings);
	void draw(int xScroll, int yScroll, int width, int height,
			  AssetManager* assets, float scaleFactorX = 1,
			  float scaleFactorY = 1);

	ofPoint& getPos();

	// in pixel:
	bool isSolid(int x, int y); // return if pixel is part of solid tile.
	int getWidth();
	int getHeight();
	int getTileWidth();
	int getTileHeight();
	int getGridX(); // return number of tiles along the x-axis.
	int getGridY(); // return number of tiles along the y-axis.
	int tileCount(); // return number of total tiles in the map.

private:
	void initTiles(ofxXmlSettings& XML);

	ofPoint pos;
	int width, height;
	int gridX, gridY;
	int tileWidth, tileHeight;

	vector<Tile> tiles;
};

#endif //MAP_H_INCLUDED
