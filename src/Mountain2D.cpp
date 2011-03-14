#include "Mountain2D.h"

void Mountain2D::setup(int width, int _height,
					   int start_iterations) {
	myLine temp;

	temp.p1.set(0, ofGetHeight() / 2, 0);
	temp.p2.set(width, ofGetHeight() / 2, 0);

	lines.push_back(temp);

	height = _height;
	smoothness = 1;
	iterations = 0;

	for(int i = 0; i < start_iterations; i++) {
		iterate();
	}
}

void Mountain2D::iterate() {
	vector<myLine>::iterator it = lines.begin();

	for(int i = 0; i < lines.size(); i+=2) {
		splitAndElevate(lines[i], height / smoothness , it);
	}
	smoothness *= 2;
	iterations++;
}

void Mountain2D::draw(int param1, int param2,
					  int param3, int param4) {
	ofPushStyle();
	for(int i = 0; i < lines.size(); i++) {
		float red = noise.noise((float)i/200.0, (float)param1/100.0,
							   (float)param4/100.0);
		float green = noise.noise((float)i/200.0, (float)param2/100.0,
							   (float)param4/100.0);
		float blue = noise.noise((float)i/200.0, (float)param3/100.0,
							   (float)param4/100.0);

		red += 1;
		green += 1;
		blue += 1;

		red /= 2;
		green /= 2;
		blue /= 2;

		//make the colors pretty bright
		red *= 400;
		green *= 400;
		blue *= 400;

		ofSetColor(red, green, blue);
		ofLine(lines[i].p1.x, lines[i].p1.y,
			   lines[i].p2.x, lines[i].p2.y);
		ofBeginShape();
			ofVertex(lines[i].p1.x, lines[i].p1.y);
			ofVertex(lines[i].p1.x, ofGetHeight());
			ofVertex(lines[i].p2.x, ofGetHeight());
			ofVertex(lines[i].p2.x, lines[i].p2.y);
		ofEndShape();
	}
	ofPopStyle();
}

void Mountain2D::splitAndElevate(myLine& oldLine, float factor,
								 vector<myLine>::iterator& it) {

	it++;
	ofPoint mid;
	mid.x = (oldLine.p2.x - oldLine.p1.x) / 2 + oldLine.p1.x;
	mid.y = (oldLine.p2.y - oldLine.p1.y) / 2 + oldLine.p1.y;

	if(iterations == 0) {
		mid.y += -0.2 * factor;
	}
	else
		mid.y += ofRandomf() * factor;

	ofPoint oldEnd;
	oldEnd.set(oldLine.p2.x, oldLine.p2.y, 0);

	oldLine.p2.set(mid.x, mid.y, 0);

	myLine newLine;
	newLine.p1.set(mid.x, mid.y, 0);
	newLine.p2.set(oldEnd.x, oldEnd.y, 0);

	newLine.color.r = oldLine.color.r * 0.8;
	newLine.color.g = oldLine.color.g * 0.8;
	newLine.color.b = oldLine.color.b * 0.8;

	it = lines.insert(it, newLine);
}