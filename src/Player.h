#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Character.h"
#include "ofxXmlSettings.h"

class Player : public Character {
public:
	Player();

	// move the player according to key-presses:
	void move(bool left, bool up, bool right,
			  bool down, Map* map);

	void kill();
	void bounce();

private:
	void derivedSetup();
	void collisionHandling(Map* map);

	float jumpheight;
	bool lockjump; // only allow jumping when on the ground.
};


#endif // PLAYER_H_INCLUDED
