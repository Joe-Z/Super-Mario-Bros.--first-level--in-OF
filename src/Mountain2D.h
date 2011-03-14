#include "ofMain.h"

#include <iostream>
#include "ofxNoise.h"
#include <vector>

struct myLine {
	ofPoint p1;
	ofPoint p2;
	ofColor color;
};
class Mountain2D {
public:
	void setup(int width, int _height,
			   int start_iterations = 0);
	void iterate();
	void draw(int param1, int param2,
			  int param3, int param4);

private:
	void splitAndElevate(myLine& oldLine, float factor,
						 vector<myLine>::iterator& it);

	vector<myLine> lines;
	int height;
	float smoothness;
	int iterations;

	ofxPerlin noise;

};