#ifndef ASSETMANAGER_H_INCLUDED
#define ASSETMANAGER_H_INCLUDED

#include <map>
#include "ofMain.h"
#include "ofxXmlSettings.h"

// asset types:
#define CHARACTER 0 // player or monster.
#define TILE 1

class AssetManager {
public:
	static AssetManager* exemplar();

	void setup(string settingsFile);
	void setup(ofxXmlSettings& XML);
	void reset(string settingsFile);

	// type can be CHARACTER or TILE:
	ofImage* getImage(string key, int type);
	ofSoundPlayer* getSound(string key);

protected:
	AssetManager();

private:
	static AssetManager* instanz; // used for singleton.

	map<string, ofImage*> tiles;
	map<string, ofImage*> players;
	map<string, ofSoundPlayer*> sounds;

	// empty the containers that hold the assets:
	void releaseAssets();

	// key is the identifying name of the asset:
	bool addImage(string key, string filename, int type);
	bool addSound(string key, string filename);

};

#endif //ASSETMANAGER_H_INCLUDED