#include "StateEnd.h"
#include "StateStart.h"

StateEnd::StateEnd():
	endScreen(new ofImage())
{
	ofAddListener(ofEvents.keyPressed, this, &StateEnd::keyPressed);
}

StateEnd::~StateEnd()
{
	delete endScreen;
	ofRemoveListener(ofEvents.keyPressed, this, &StateEnd::keyPressed);
}

void StateEnd::setup(StateManager* manager)
{
	_manager = manager;

	endScreen->loadImage("end_screen.png");
	timer = ofGetElapsedTimeMillis();
}

void StateEnd::update()
{
	if(ofGetElapsedTimeMillis() - timer >= 5000) {
		OF_EXIT_APP(0);
	}
}

void StateEnd::draw()
{
	endScreen->draw(0, 0, ofGetWidth(), ofGetHeight());
	string info = "press space to return to start menu\n";
	info += "game will close in ";
	info += ofToString((-(ofGetElapsedTimeMillis()-
					   timer - 5000)) / 1000);
	info += " seconds";
	ofDrawBitmapString(info, ofGetWidth() / 2, 100);
}


void StateEnd::keyPressed(ofKeyEventArgs & _args)
{
	int key=_args.key;

	if(key==' ') 
		changeState(_manager, new StateStart());
}
