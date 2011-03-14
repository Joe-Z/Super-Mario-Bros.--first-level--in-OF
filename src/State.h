#pragma once

class StateManager;

#include "ofMain.h"

class State {

public:
	virtual void setup(StateManager* manager) = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual ~State();

protected:

	void changeState(StateManager* manager, State* state);

	StateManager *_manager;
};
