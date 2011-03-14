#pragma once
#include "State.h"
#include "StateManager.h"

State::~State()
{
}

void State::changeState(StateManager* manager, State* state){
	manager->changeState(state);
}
