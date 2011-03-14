#pragma once

#include <cmath>
#include <list>
#include "State.h"
#include "AssetManager.h"
#include "Player.h"
#include "Monster.h"
#include "Map.h"

class StateManager;

class StateRunning : public State {

public:	
	StateRunning();
	virtual ~StateRunning();

	virtual void setup(StateManager* manager);
	virtual void draw();
	virtual void update();
	
	
private:
	void keyPressed(ofKeyEventArgs & _args);
	void keyReleased(ofKeyEventArgs & _args);
	void keyHandle(bool pressed, int key);

	void updateScroll(ofPoint& scroll, Player* player);
	bool charCollision(Character* char1, Character* char2);

	AssetManager* assets;

	Player* player1;
	Player* player2;

	list<Monster*> monsters;
	int monsterCount;

	Map* map;
	string bgSound;

	// scroll coords of the players:
	ofPoint scroll1, scroll2;

	// scale depending on vertical/horizontal screen division:
	float scaleFactorX;
	float scaleFactorY;

	// movement state of the players:
	bool left1, up1, right1, down1;
	bool left2, up2, right2, down2;
};
