#include "StateRunning.h"
#include "StateEnd.h"

StateRunning::StateRunning():
	player1(new Player()),
	player2(new Player()),
	map(new Map()) {

	ofAddListener(ofEvents.keyPressed, this, &StateRunning::keyPressed);
	ofAddListener(ofEvents.keyReleased, this, &StateRunning::keyReleased);
}

StateRunning::~StateRunning()
{
	//stop sound:
	assets->getSound(bgSound)->stop();
	delete player1;
	delete player2;
	delete map;
	ofRemoveListener(ofEvents.keyPressed, this, &StateRunning::keyPressed);
	ofRemoveListener(ofEvents.keyReleased, this, &StateRunning::keyReleased);
}

void StateRunning::setup(StateManager* manager)
{
	_manager = manager;

	assets = AssetManager::exemplar();

	assets->setup("2d_map_extended.xml");

	map->initMap("2d_map_extended.xml");

	player1->init("2d_map_extended_characters.xml", "PLAYER_1");
	player2->init("2d_map_extended_characters.xml", "PLAYER_2");

	//initialize monsters
	monsterCount = 10;
	for(int i = 1; i <= monsterCount; i++) {
		int x = map->getWidth() / monsterCount * i;
		int y = 0;
		Monster* monstrPtr = new Monster(x, y);

		monsters.push_back(monstrPtr);

		monsters.back()->init("2d_map_extended_characters.xml", "ENEMY_1");
	}

	//load XML-parser
	ofxXmlSettings XML;

	if(XML.loadFile("2d_map_extended_characters.xml")) {
		cout << "Processing Settings for testApp!" << endl;
	}
	else {
		cout << "Couldn't load Settings-File for testApp!" << endl;
	}

	int frameRate = XML.getValue("GAME:SETTINGS:FRAMERATE", 30);
	bool fullScreen = XML.getValue("GAME:SETTINGS:FULLSCREEN", 0);
	bool debug = XML.getValue("GAME:SETTINGS:DEBUG", 1);
	bgSound = XML.getValue("GAME:SETTINGS:BACKGROUND_MUSIC", "");

	if(bgSound != "") {
		assets->getSound(bgSound)->play();
	}

	scroll1.set(0, 0, 0);
	scroll2.set(0, 0, 0);

	scaleFactorX = 1;
	scaleFactorY = 2;

	left1 = up1 = right1 = down1 = false;
	left2 = up2 = right2 = down2 = false;

	ofSetFrameRate(frameRate);
	ofSetFullscreen(fullScreen);

	//set background-color to default smb-blue
	ofBackground(92, 148, 252);
}

void StateRunning::update()
{
	//check if one of the players is at the level-end
	if(player1->getX() / map->getTileWidth() >= map->getGridX() - 1 ||
		player2->getX() / map->getTileWidth() >= map->getGridX() - 1) {
			ofSleepMillis(1000);	
			changeState(_manager, new StateEnd());
	}
	else {
	// update player-position and scroll coords:
	player1->move(left1, up1, right1, down1, map);
	updateScroll(scroll1, player1);

	player2->move(left2, up2, right2, down2, map);
	updateScroll(scroll2, player2);

	float gravity = player1->getGravity();
	for(list<Monster*>::iterator it = monsters.begin();
		it != monsters.end();) {

		(*it)->move(map);

		if((*it)->getStatus() != dead &&
		   (*it)->getStatus() != dying) {
			if(charCollision(player1, (*it)) &&
				player1->getStatus() != dead) {
				//if player is moving down
				if(player1->getVelY() > gravity) {
					player1->bounce();
					(*it)->bruise();
				}
				else
					player1->kill();
			}
		}
		//test if the monster is still alive
		if((*it)->getStatus() != dead &&
		   (*it)->getStatus() != dying) {
			if(charCollision(player2, (*it)) &&
				player2->getStatus() != dead) {
				//if player is moving down
				if(player2->getVelY() > gravity) {
					player2->bounce();
					(*it)->bruise();
				}
				else
					player2->kill();
			}
		}

		if((*it)->getStatus() == dead) {
			   it = monsters.erase(it);
			   continue;
		}
		else
			it++;

	} // end of for-loop

	} //end of else
}

void StateRunning::draw()
{
	//upper half window, player 1:
	glViewport(0, ofGetHeight() / 2 + 2, ofGetWidth(), ofGetHeight() / 2 - 2);
	glPushMatrix();
	ofEnableAlphaBlending();
	ofTranslate(scroll1.x * scaleFactorX, scroll1.y * scaleFactorY);
	gluOrtho2D(0, 2, 0, 1);

	map->draw(scroll1.x, scroll1.y, ofGetWidth(), ofGetHeight() / 2,
			  assets);

	// draw player one in the front:
	player2->draw(assets);
	player1->draw(assets);

	for(list<Monster*>::iterator it = monsters.begin();
		it != monsters.end(); it++) {

		(*it)->draw(assets);
	}
	
	ofDisableAlphaBlending();
	glPopMatrix();

	//// border between the two viewports, draw seperation graphic here:
	//glViewport(0, ofGetHeight() / 2 + 2, ofGetWidth(), 4);

	// lower half window, player 2:
	glViewport(0, 0, ofGetWidth(), ofGetHeight() / 2 - 2);
	glPushMatrix();
	ofEnableAlphaBlending();
	ofTranslate(scroll2.x * scaleFactorX, scroll2.y * scaleFactorY);
	gluOrtho2D(0, 2, 0, 1);

	map->draw(scroll2.x, scroll2.y, ofGetWidth(), ofGetHeight(),
			  assets);

	// draw player two in the front:
	player1->draw(assets);
	player2->draw(assets);

	for(list<Monster*>::iterator it = monsters.begin();
		it != monsters.end(); it++) {

		(*it)->draw(assets);
	}

	ofDisableAlphaBlending();
	glPopMatrix();

	//viewport-overlay for misc. output
	glViewport(0, 0, ofGetWidth(), ofGetHeight());
	glPushMatrix();
	ofPushStyle();
		ofSetColor(255, 255, 255);
		string controls = "press 'q' to quit";
		ofDrawBitmapString(controls, ofGetWidth() / 2 - 200,
						   ofGetHeight() - 10);
	ofPopStyle();
	glPopMatrix();
}


void StateRunning::keyPressed(ofKeyEventArgs & _args)
{
	int key=_args.key;

	keyHandle(true, key);

	switch(key) {
		case 'q':
			changeState(_manager, new StateEnd());
			break;
	}
}

void StateRunning::keyReleased(ofKeyEventArgs & _args)
{
	int key=_args.key;

	keyHandle(false, key);
}

void StateRunning::keyHandle(bool pressed, int key) {

	// handle controls:
	key = tolower(key);
	switch(key) {
	case OF_KEY_LEFT:
		left1 = pressed;
		break;
	case OF_KEY_UP:
		up1 = pressed;
		break;
	case OF_KEY_RIGHT:
		right1 = pressed;
		break;
	case OF_KEY_DOWN:
		down1 = pressed;
		break;
	case 'w':
		up2 = pressed;
		break;
	case 'a':
		left2 = pressed;
		break;
	case 's':
		down2 = pressed;
		break;
	case 'd':
		right2 = pressed;
		break;
	default:
		cout << key << endl;
		break;
	}
}

bool StateRunning::charCollision(Character* char1, Character* char2) {
	int left1, left2;
	int right1, right2;
	int top1, top2;
	int bottom1, bottom2;

	left1 = char1->getX();
	left2 = char2->getX();
	right1 = left1 + char1->getWidth();
	right2 = left2 + char2->getWidth();

	top1 = char1->getY();
	top2 = char2->getY();
	bottom1 = top1 + char1->getHeight();
	bottom2 = top2 + char2->getHeight();
	
	//the first 4 cases are the ones
	//where intersection is impossible
	if(right1 < left2) {
		return false;
	}
	else if(bottom1 < top2) {
		return false;
	}
	else if(left1 > right2) {
		return false;
	}
	else if(top1 > bottom2) {
		return false;
	}
	//so here we must have a collision
	else {
		return true;
	}
}

void StateRunning::updateScroll(ofPoint& scroll, Player* player) {

	// keep every player in the center of his screen-half:
	scroll.x = -player->getX() + ofGetWidth() / (scaleFactorX * 2);
	scroll.y = -player->getY() + ofGetHeight() / (scaleFactorY * 2);

	// don't scroll out of the map-boundaries:
	if(scroll.x > 0)
		scroll.x = 0;
	else if(scroll.x < (-map->getWidth() + ofGetWidth() / scaleFactorX))
		scroll.x = -map->getWidth() + ofGetWidth() / scaleFactorX;

	if(scroll.y > 0)
		scroll.y = 0;
	else if(scroll.y < -map->getHeight() + ofGetHeight() / scaleFactorY)
		scroll.y = -map->getHeight() + ofGetHeight() / scaleFactorY;

}