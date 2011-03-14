#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "StateManager.h"

class testApp : public ofBaseApp {

public:

	testApp();
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);

	StateManager manager;

};

#endif //_TEST_APP