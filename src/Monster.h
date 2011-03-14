#ifndef MONSTER_H_INCLUDED
#define MONSTER_H_INCLUDED

#include "Character.h"
#include "ofxXmlSettings.h"

class Monster : public Character {
public:
	Monster(int x, int y);

	// move the monster
	void move(Map* map);

private:
	void derivedSetup();
	void collisionHandling(Map* map);

	int startX, startY;

	bool movingLeft, movingRight;
};

#endif //MONSTER_H_INCLUDED
