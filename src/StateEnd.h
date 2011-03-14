#pragma once

#include "State.h"
#include "ofMain.h"

class StateManager;

class StateEnd : public State {

public:	
	StateEnd();
	virtual ~StateEnd();

	virtual void setup(StateManager* manager);
	virtual void draw();
	virtual void update();
	
	
private:
	void keyPressed(ofKeyEventArgs & _args);
	ofImage* endScreen;

	int timer;
};
