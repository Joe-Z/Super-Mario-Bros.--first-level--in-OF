#pragma once

#include "ofMain.h"

class State;

class StateManager {
public:
	StateManager();
	~StateManager();

	void draw();
	void update();

	void changeState(State* state);

private:
	
	State* _curState;
};