#pragma once

#include "State.h"

class StateLoading : public State {

public:	
	StateLoading();
	virtual ~StateLoading();

	virtual void setup(StateManager* manager);
	virtual void draw();
	virtual void update();
	
private:
	ofImage* loadScreen;
	bool drawnOnce;
};
