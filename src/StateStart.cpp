#include "StateManager.h"
#include "StateStart.h"
#include "StateLoading.h"
#include "StateEnd.h"

StateStart::StateStart():
	startScreen(new ofImage())
{
	ofAddListener(ofEvents.keyPressed, this, &StateStart::keyPressed);
}

StateStart::~StateStart()
{
	delete startScreen;
	ofRemoveListener(ofEvents.keyPressed, this, &StateStart::keyPressed);
}

void StateStart::setup(StateManager* manager)
{
	_manager = manager;
	startScreen->loadImage("start_screen.png");
}

void StateStart::update()
{
}

void StateStart::draw()
{
	startScreen->draw(0, 0, ofGetWidth(), ofGetHeight());
	string info = "press enter to start game\n";
	info += "or 'q' to quit";
	ofDrawBitmapString(info, ofGetWidth() / 2, 100);
}


void StateStart::keyPressed(ofKeyEventArgs & _args)
{
	int key=_args.key;

	switch(key) {
		case OF_KEY_RETURN:
			changeState(_manager, new StateLoading());
			break;
		case 'q':
			changeState(_manager, new StateEnd());	
			break;
	}
}
