//
//  recorder.h
//  week3_multiPointRecorders
//
//  Created by Matt on 10/1/12.
//
//

#ifndef __week3_multiPointRecorders__recorder__
#define __week3_multiPointRecorders__recorder__

#include <iostream>
#include "ofMain.h"
#include "timePoint.h"

class recorder {

public:
	
	void setup(int hue, int shape);
	void draw();
	
	void clear();
	
	void start(float x, float y);
	void add(float x, float y);
	void end();

	bool drawable();
	void drawShape();
	
	ofPoint positionForTime(float time);
	float angleForTime(float time);
	
	void setShapeCount(int count);
	
	bool recording;
	float startTime;
	vector <timePoint> points;
	
	ofColor color;
	int shapeType;
	int shapeCount;
	bool showPath;
	
};

#endif /* defined(__week3_multiPointRecorders__recorder__) */
