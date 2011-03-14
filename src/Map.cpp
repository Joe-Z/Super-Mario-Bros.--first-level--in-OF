#include "Map.h"

Map::Map():
	width(0), /* width in pixels */
	height(0), /* height in pixels */
	gridX(0), /* width in tiles */
	gridY(0), /* height in tiles */
	tileWidth(0), /* width of the tiles */
	tileHeight(0) { /* height the tiles */
}

void Map::initMap(string settings) {
	//load XML-parser
	ofxXmlSettings XML;

	if(XML.loadFile(settings)) {
		cout << "Processing Settings for map!" << endl;

		gridX = XML.getValue("GAME:MAP:GRID:X", 1);
		gridY = XML.getValue("GAME:MAP:GRID:Y", 1);

		tileWidth = XML.getValue("GAME:MAP:TILES:PROPERTIES:WIDTH", 10);
		tileHeight = XML.getValue("GAME:MAP:TILES:PROPERTIES:HEIGHT", 10);

		width = gridX * tileWidth;
		height = gridY * tileHeight;

		initTiles(XML);
	}
	else {
		cout << "Couldn't load Settings-File for map!" << endl;
	}

}

void Map::initTiles(ofxXmlSettings& XML) {
	cout << "\tProcessing tiles for map!" << endl;

	// this temporarily treats the tag as the document root:
	XML.pushTag("GAME");
	XML.pushTag("MAP");
	XML.pushTag("TILES");
	XML.pushTag("DATA");

	// read the tiles from the xml file and write it into a vector:
	for(int i = 0; i < gridX * gridY; i++) {
		string tempFileName = XML.getValue("TILE:PATH", "error.png", i);
		bool solid = XML.getValue("TILE:STATE", 0, i);

		// create temporary tile to push back:
		Tile tempTile(solid, tempFileName);
		tiles.push_back(tempTile);
	}

	XML.popTag(); // DATA
	XML.popTag(); // TILES
	XML.popTag(); // MAP
	XML.popTag(); // GAME
}

void Map::draw(int xScroll, int yScroll, int width, int height,
			   AssetManager* assets,
			   float scaleFactorX,
			   float scaleFactorY) {

   // get tile-coordinates:
   int xPos = -xScroll;
   int yPos = -yScroll;
   int tileX = floor(float(xPos / tileWidth));
   int tileY = floor(float(yPos / tileHeight));
   
   int rightBorder = int((xPos + width) / tileWidth);
   //increase border but make sure it stays in boundaries
   rightBorder = ofClamp(rightBorder + 1, 0, gridX);

   int bottomBorder = int((yPos + height) / tileHeight);
   //increase border but make sure it stays in boundaries
   bottomBorder = ofClamp(bottomBorder + 1, 0, gridY);

	// draw the tiles:
	int n = 0;
	for(int y = tileY; y < bottomBorder; y++) { // for every row:
		for(int x = tileX; x < rightBorder; x++) { // for every column:
			n = y * gridX + x;
					ofImage* tempImage;
					tempImage = assets->getImage(tiles[n].imagePath, TILE);
					// draw the corresponding tile:
					if(tempImage != 0) {
						tempImage->draw((x * tileWidth) * scaleFactorX,
										(y * tileHeight) * scaleFactorY,
										tileWidth * scaleFactorX, tileHeight * scaleFactorY);
					}
		}
	}
}

bool Map::isSolid(int x, int y) {
	
	//game would crash if you try to
	//access a pixel out of vector-range
	x = ofClamp(x, 0, gridX - 1);
	y = ofClamp(y, 0, gridY - 1);

	int i = y * gridX + x;

	if(tiles[i].solid == true)
		return true;
	else
		return false;
}

ofPoint& Map::getPos() {
	return pos;
}

int Map::getWidth() {
	return int(gridX * tileWidth);
}

int Map::getHeight() {
	return int(gridY * tileHeight);
}

int Map::getTileWidth() {
	return tileWidth;
}

int Map::getTileHeight() {
	return tileHeight;
}

int Map::getGridX() {
	return gridX;
}

int Map::getGridY() {
	return gridY;
}

int Map::tileCount() {
	return (int)tiles.size();
}