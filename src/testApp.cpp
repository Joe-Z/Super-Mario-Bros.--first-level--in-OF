#include "testApp.h"

//--------------------------------------------------------------
testApp::testApp() {
}

//--------------------------------------------------------------
void testApp::setup() {
	ofSetVerticalSync(true);
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void testApp::update() {
	ofSetWindowTitle(ofToString(ofGetFrameRate()));

	manager.update();
}


//--------------------------------------------------------------
void testApp::draw() {
	manager.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key) {
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
}
