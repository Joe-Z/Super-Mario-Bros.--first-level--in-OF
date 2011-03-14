#include "StateManager.h"
#include "StateStart.h"
#include "StateRunning.h"

StateManager::StateManager()
{
	_curState = NULL;

	// by default, we start with StateStart
	changeState( new StateStart() );
}

StateManager::~StateManager()
{
}

void StateManager::changeState(State * state)
{
	if ( state != _curState )
	{
		if(_curState!=NULL)
			delete _curState;

		_curState = state;
		_curState->setup(this);
	}
}

void StateManager::update()
{
	_curState->update();
}

void StateManager::draw()
{
	_curState->draw();
}
