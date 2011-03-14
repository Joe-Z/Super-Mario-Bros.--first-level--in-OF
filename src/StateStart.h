#pragma once

#include "State.h"

class StateStart : public State {

public:	
	StateStart();
	virtual ~StateStart();

	virtual void setup(StateManager* manager);
	virtual void draw();
	virtual void update();
	
	
private:
	void keyPressed(ofKeyEventArgs & _args);
	ofImage* startScreen;
};
