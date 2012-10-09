//
//  recorder.cpp
//  week3_multiPointRecorders
//
//  Created by Matt on 10/1/12.
//
//

#include "recorder.h"

void recorder::setup(int hue, int shape) {

	recording = false;
	startTime = 0;
	
	color = ofColor::fromHsb(hue % 255, 255, 255);
	shapeType = shape % 3;
	shapeCount = 1;
	
}


void recorder::draw() {

	if (showPath) {

		ofNoFill();
		ofSetColor(255);
		ofSetLineWidth(3);
		
		ofBeginShape();
		
		for (int i = 0; i < points.size(); i++) {
			ofVertex(points[i].pos.x, points[i].pos.y);
		}
		
		ofEndShape();

	}
}



void recorder::clear() {

	points.clear();
	
}


void recorder::start(float x, float y) {

	timePoint p;
	
	p.pos.x = x;
	p.pos.y = y;
	p.t = 0;
	
	points.clear();
	points.push_back(p);
	
	recording = true;
	startTime = ofGetElapsedTimef();
	showPath = true;
	
}

void recorder::add(float x, float y) {
	
	timePoint p;
	
	p.pos.x = x;
	p.pos.y = y;
	p.t = ofGetElapsedTimef() - startTime;
	
	points.push_back(p);
	
}


void recorder::end() {

	recording = false;
	showPath = false;
	
}


bool recorder::drawable() {
	
	if (!recording && points.size() >= 2)
		return true;
	else
		return false;
	
}

void recorder::drawShape() {
	
	ofFill();
	ofSetColor(color);

	float duration = points[points.size()-1].t;
	
	float time = ofGetElapsedTimef();
	float offsetTime = time - startTime;
	float timePos = fmod(offsetTime, duration);

	float multiShapeOffset = duration / shapeCount;
	
	for (int i = 0; i < shapeCount; i++) {
	
		float offsetForCurrentPoint = fmod(timePos + (multiShapeOffset * i), duration);
		
		ofPoint p = positionForTime(offsetForCurrentPoint);
		float theta = angleForTime(offsetForCurrentPoint);
		
		ofPushMatrix();
		ofTranslate(p.x, p.y);
		ofRotateZ(-theta);

		if (shapeType == 0)
			ofEllipse(0, 0, 100, 100);
		if (shapeType == 1)
			ofRect(0, 0, 100, 100);
		if (shapeType == 2)
			ofTriangle(0, 35, 50, -50, -50, -50);
		
		ofPopMatrix();
		
	}
	
}

ofPoint recorder::positionForTime(float time) {
	
	ofPoint p;
	
	for (int i = 0; i < points.size() - 1; i++) {
		
		if (points[i].t <= time && time <= points[i+1].t) {
			
			float timeDiff = time - points[i].t;
			float pointDuration = points[i+1].t - points[i].t;
			float percent = timeDiff / pointDuration;
			
			p.x = points[i].pos.x * (1-percent) + points[i+1].pos.x * percent;
			p.y = points[i].pos.y * (1-percent) + points[i+1].pos.y * percent;
			
			return p;
			
		}
		
	}
	
}

float recorder::angleForTime(float time) {

	for (int i = 0; i < points.size() - 1; i++) {
		
		if (points[i].t <= time && time <= points[i+1].t) {
			
			float x = points[i+1].pos.x - points[i].pos.x;
			float y = points[i+1].pos.y - points[i].pos.y;
			
			float theta = atan2(x, y);
			return theta * RAD_TO_DEG;
			
		}
		
	}
	
}

void recorder::setShapeCount(int count) {
	
	shapeCount = count;
	
}

