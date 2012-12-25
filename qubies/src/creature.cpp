//
//  creature.cpp
//  muscles
//
//  Created by Matt on 11/18/12.
//
//

#include "creature.h"
#include "ofxAccelerometer.h"

extern vector <bool> touchStatus;
extern vector <float> touchX, touchY;

void creature::setup(ofColor color, float size, ofPolyline ground) {

	dead = false;
	earthquake = false;
	
	this->color = color;
	this->size = size;
	this->ground = ground;
	
	pos.y = ofGetHeight() / 2;
	//pos.x = ofGetWidth() / 2;
	pos.x = ofRandom(ofGetWidth() - size*2);
	
	//float vx = ofRandom(-5, 5);
	//float vy = ofRandom(-5, 5);
	float vx = (((int) ofRandom(2) == 0) ? 1 : -1) * ofRandom(4, 8);
	float vy = -1 * ofRandom(4, 8);
	
	// scale sine wave a bit when expanding muscles so that
	// all creatures hop at different rates
	sinOffset = ofRandom(0.8, 1.2);
	
	// create a square body out of 4 points
	particle *p1 = new particle();
	particle *p2 = new particle();
	particle *p3 = new particle();
	particle *p4 = new particle();
	
	p1->setInitialCondition(pos.x,pos.y, vx, vy);
	particles.push_back(p1);
	
	p2->setInitialCondition(pos.x,pos.y + size, 0, 0);
	particles.push_back(p2);
	
	p3->setInitialCondition(pos.x+size, pos.y+size, vx, vy);
	particles.push_back(p3);
	
	p4->setInitialCondition(pos.x+size, pos.y, vx, vy);
	particles.push_back(p4);
	
	// create springs for edges
	createSpring(p1, p2);
	createSpring(p2, p3);
	createSpring(p3, p4);
	createSpring(p4, p1);
	
	// cross braces for stability
	createSpring(p2, p4);
	createSpring(p1, p3);
	
	
	
	// feet
	// the feet are a little in from the edge and a little below
	// 1/8 the body size in
	// 1/3 the body size down
	particle *p5 = new particle();
	particle *p6 = new particle();
	
	p5->setInitialCondition(pos.x+size/8,pos.y+size+size/3, vx, vy);
	particles.push_back(p5);
	
	p6->setInitialCondition(pos.x+size*7/8, pos.y+size+size/3, vx, vy);
	particles.push_back(p6);
	
	
	// inner hip
	// hips are double the width of the feet
	// i.e. feet are 1/8 body size, hips are 1/4 body size
	particle *p7 = new particle();
	particle *p8 = new particle();
	
	p7->setInitialCondition(pos.x+size/4,pos.y+size, vx, vy);
	particles.push_back(p7);
	
	p8->setInitialCondition(pos.x+size*3/4,pos.y+size, vx, vy);
	particles.push_back(p8);
	
	
	
	// create springs for feet & hips
	// left hip cross bracing
	createSpring(p7, p2);
	createSpring(p7, p1);
	
	// right hip cross bracing
	createSpring(p8, p3);
	createSpring(p8, p4);
	
	// left foot to hips
	createSpring(p5, p2, true);
	createSpring(p5, p7, true);
	
	// right foot to hips
	createSpring(p6, p3, true);
	createSpring(p6, p8, true);
	
	// left hip to right hip fro more stability
	createSpring(p7, p8);
	

	// arms
	particle *p9 = new particle();
	particle *p10 = new particle();
	particle *p11 = new particle();
	particle *p12 = new particle();
	
	p9->setInitialCondition(pos.x, pos.y + size/2, vx, vy);
	particles.push_back(p9);
	
	p10->setInitialCondition(pos.x + size, pos.y + size/2, vx, vy);
	particles.push_back(p10);

	p11->setInitialCondition(pos.x - size/3, pos.y + size/2, vx, vy);
	particles.push_back(p11);
	
	p12->setInitialCondition(pos.x + size + size/3, pos.y + size/2, vx, vy);
	particles.push_back(p12);
	
	// create springs for edges
	createSpring(p9, p1);
	createSpring(p9, p2);
	createSpring(p10, p3);
	createSpring(p10, p4);
	
	createSpring(p11, p9);
	createSpring(p12, p10);
}

void creature::update() {

	// calculate the the muscle length depending on if it's a big guy or little guy
	float muscleLength = size < 75 ? 7 : 20;

	// calculate the shake amount if there's an earthquake
	float shakeAmountX = ((ofRandom(0, 1) > 0.5) ? -1 : 1) * ofRandom(3, 6);
	float shakeAmountY = ofRandom(-8, -6);
	
	for (int i = 10; i < 14; i++) {
		// set spring distance to rest length + however much we're stretching
		// multiply the sine offset so there's some diversity in hop rate
		springs[i].distance = springs[i].restLength + muscleLength * sin(ofGetElapsedTimef()*8 * sinOffset);
	}
	
	
	for (int i = 0; i < particles.size(); i++){
		particles[i]->resetForce();
	}
	

	// (A) calculate centroid (add up all particles and divide by num particles)
	// (B) calc pct on screen
	// (C) +- some pct to check
	// (D) just check against ground on those + - pct converted to ground scale (pct * nGroundPts)
	
//	ofPoint centroid = this->centroid();
//	float xPct = centroid.x / ofGetWidth();
//	
//	
	for (int i = 0; i < particles.size(); i++){
		// gravity
		particles[i]->addForce(0,0.1f);

		// x component of accelerometer
		particles[i]->addForce(0.25 * ofxAccelerometer.getForce().y, 0);
		
		for (int j = 0; j < touchStatus.size(); j++) {
			if (touchStatus[j])
				particles[i]->addRepulsionForce(touchX[j], touchY[j], 150, 3);
		}
		
		// ground
//		vector <ofPoint> groundPoints = ground.getVertices();
//		float pointCount = groundPoints.size();
//		int pointStart = pointCount * (xPct - 0.1);
//		int pointEnd = pointCount * (xPct + 0.1);
//
//		for (int j = pointStart; j < pointEnd; j++) {
//			//cout << "repelling from " << groundPoints[j].x << " " << groundPoints[j].y << endl;
//			//if (ofPoint(groundPoints[j].x, groundPoints[j].y).distance(particles[i]->pos) <= 10) {
//				particles[i]->addRepulsionForce(groundPoints[j].x, groundPoints[j].y, 10, 5);
//			//}
//		}
		
		// shake up with an earthquake
		if (earthquake) {
			particles[i]->addForce(shakeAmountX, shakeAmountY);
		}
	}
	
	for (int i = 0; i < springs.size(); i++){
		springs[i].update();
	}
	
	for (int i = 0; i < particles.size(); i++){
		particles[i]->bounceOffWalls();
		particles[i]->addDampingForce();
		particles[i]->update();
	}

	
	// Check if creature was flung off top
	// Set flag to true, and check each particle. If any of the particles
	// are below the top of the screen, set the flag to false and break
	// out of the loop to save ourselves some cpu time
	bool flungOffTop = true;
	for (int i = 0; i < particles.size(); i++) {
		if (particles[i]->pos.y > 0) {
			flungOffTop = false;
			break;
		}
	}
	
	// Set dead to true and testApp will remove this creature from its list
	if (flungOffTop) {
		//ofBackground(ofColor::fromHsb(ofRandom(255), 200, 200));
		particles.clear();
		springs.clear();
		dead = true;
	}
	
	earthquake = false;
}

void creature::draw() {
	
	ofSetColor(color);
	ofFill();
	
	//	for (int i = 0; i < particles.size(); i++){
	//		particles[i]->draw();
	//	}
	//
	
	ofSetLineWidth(size/15);
	for (int i = springs.size() - 1; i >= springs.size() - 2; i--){
	//for (int i = 0; i < springs.size(); i++) {
		springs[i].draw();
	}
	
	// draw the whole thing as one shape so that you can tell
	// when the feet are inside the body. kind of cute!
	
	ofSetLineWidth(0);
	
	/*
	ofBeginShape();
	
	ofVertex(particles[0]->pos.x, particles[0]->pos.y);
	ofVertex(particles[1]->pos.x, particles[1]->pos.y);
	
	ofVertex(particles[4]->pos.x, particles[4]->pos.y);
	
	ofVertex(particles[6]->pos.x, particles[6]->pos.y);
	ofVertex(particles[7]->pos.x, particles[7]->pos.y);
	
	ofVertex(particles[5]->pos.x, particles[5]->pos.y);
	
	ofVertex(particles[2]->pos.x, particles[2]->pos.y);
	ofVertex(particles[3]->pos.x, particles[3]->pos.y);
	
	ofVertex(particles[0]->pos.x, particles[0]->pos.y);
	
	ofEndShape();
	*/
	
	
	// different method for drawing the creature with different
	// shapes for body and legs. i like it a bit more.
//	ofBeginShape();
//	ofVertex(particles[0]->pos.x, particles[0]->pos.y);
//	ofVertex(particles[1]->pos.x, particles[1]->pos.y);
//	ofVertex(particles[2]->pos.x, particles[2]->pos.y);
//	ofVertex(particles[3]->pos.x, particles[3]->pos.y);
//	ofEndShape();
//	
//	ofBeginShape();
//	ofVertex(particles[1]->pos.x, particles[1]->pos.y);
//	ofVertex(particles[4]->pos.x, particles[4]->pos.y);
//	ofVertex(particles[6]->pos.x, particles[6]->pos.y);
//	ofEndShape();
//
//	ofBeginShape();
//	ofVertex(particles[2]->pos.x, particles[2]->pos.y);
//	ofVertex(particles[5]->pos.x, particles[5]->pos.y);
//	ofVertex(particles[7]->pos.x, particles[7]->pos.y);
//	ofEndShape();
	
	ofMesh mesh;
	mesh.setMode(OF_PRIMITIVE_TRIANGLES);
	
	mesh.addVertex(particles[0]->pos);
	mesh.addVertex(particles[1]->pos);
	mesh.addVertex(particles[2]->pos);
	
	mesh.addVertex(particles[2]->pos);
	mesh.addVertex(particles[3]->pos);
	mesh.addVertex(particles[0]->pos);
	
	mesh.draw();
	mesh.clear();
	
	mesh.addVertex(particles[1]->pos);
	mesh.addVertex(particles[4]->pos);
	mesh.addVertex(particles[6]->pos);

	mesh.draw();
	mesh.clear();

	mesh.addVertex(particles[2]->pos);
	mesh.addVertex(particles[5]->pos);
	mesh.addVertex(particles[7]->pos);

	mesh.draw();

	// draw the eyes
	// calculate a point partway between the top two points
	// calculate a point partway between the bottom two points
	// then calculate a point partway between these two points
	ofPoint leftShiftedTop = particles[0]->pos.getInterpolated(particles[3]->pos, 0.15);
	ofPoint leftShiftedBot = particles[1]->pos.getInterpolated(particles[2]->pos, 0.15);
	ofPoint leftEye = leftShiftedTop.getInterpolated(leftShiftedBot, 0.15);

	ofPoint rightShiftedTop = particles[0]->pos.getInterpolated(particles[3]->pos, 0.85);
	ofPoint rightShiftedBot = particles[1]->pos.getInterpolated(particles[2]->pos, 0.85);
	ofPoint rightEye = rightShiftedTop.getInterpolated(rightShiftedBot, 0.15);
	
	ofSetColor(50, 200);
	ofCircle(leftEye, size/13);
	ofCircle(rightEye, size/13);
	
}

void creature::createSpring(particle * p1, particle * p2) {
	createSpring(p1, p2, false);
}

void creature::createSpring(particle * p1, particle * p2, bool shouldBeStiffer) {
	
	spring s;
	
	s.restLength	= (p1->pos - p2->pos).length();
	s.springiness	= 0.3f;
	s.particleA		= p1;
	s.particleB		= p2;
	
	s.distance = s.restLength;
	
	if (shouldBeStiffer)
		s.springiness = 0.5f;
	
	springs.push_back(s);
}

void creature::shakeUp() {
	earthquake = true;
}

ofPoint creature::centroid() {
	
	// Calculate centroid by looking at first 4 points (the corners of the body)
	// and ignore the rest (hips, feet, arms, etc.)
	
	ofPoint centroid = ofPoint(0, 0);

	for (int i = 0; i < 4; i++) {
		centroid += particles[i]->pos;
	}
	
	centroid /= 4;
	
	return centroid;
}

/*
void creature::repelMouse(float x, float y) {
	mouseX = x;
	mouseY = y;
}
*/

