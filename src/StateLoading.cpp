#include "StateManager.h"
#include "StateLoading.h"
#include "StateRunning.h"

StateLoading::StateLoading():
	loadScreen(new ofImage())
{
	drawnOnce = false;
}

StateLoading::~StateLoading()
{
	delete loadScreen;
}

void StateLoading::setup(StateManager* manager)
{
	_manager = manager;
	loadScreen->loadImage("load_screen.png");
}

void StateLoading::update()
{
	if(drawnOnce)
		changeState(_manager, new StateRunning());
}

void StateLoading::draw()
{
	loadScreen->draw(0, 0, ofGetWidth(), ofGetHeight());
	drawnOnce = true;
}

