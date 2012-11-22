//
//  creature.cpp
//  muscles
//
//  Created by Matt on 11/18/12.
//
//

#include "creature.h"

void creature::setup(ofColor color, float size) {

	this->color = color;
	this->size = size;
	
	pos.y = 600;
	pos.x = ofRandom(ofGetWidth() - size*2);
	
	// scale sine wave a bit when expanding muscles so that
	// all creatures hop at different rates
	sinOffset = ofRandom(0.8, 1.2);
	
	// create a square body out of 4 points
	particle *p1 = new particle();
	particle *p2 = new particle();
	particle *p3 = new particle();
	particle *p4 = new particle();
	
	p1->setInitialCondition(pos.x,pos.y,0,0);
	particles.push_back(p1);
	
	p2->setInitialCondition(pos.x,pos.y + size,0,0);
	particles.push_back(p2);
	
	p3->setInitialCondition(pos.x+size, pos.y+size,0,0);
	particles.push_back(p3);
	
	p4->setInitialCondition(pos.x+size, pos.y,0,0);
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
	// 1/4 the body size down
	particle *p5 = new particle();
	particle *p6 = new particle();
	
	p5->setInitialCondition(pos.x+size/8,pos.y+size+size/4,0,0);
	particles.push_back(p5);
	
	p6->setInitialCondition(pos.x+size*7/8, pos.y+size+size/4,0,0);
	particles.push_back(p6);
	
	
	// inner hip
	// hips are double the width of the feet
	// i.e. feet are 1/8 body size, hips are 1/4 body size
	particle *p7 = new particle();
	particle *p8 = new particle();
	
	p7->setInitialCondition(pos.x+size/4,pos.y+size,0,0);
	particles.push_back(p7);
	
	p8->setInitialCondition(pos.x+size*3/4,pos.y+size,0,0);
	particles.push_back(p8);
	
	
	
	// create springs for feet & hips
	// left hip cross bracing
	createSpring(p7, p2);
	createSpring(p7, p1);
	
	// right hip cross bracing
	createSpring(p8, p3);
	createSpring(p8, p4);
	
	// left foot to hips
	createSpring(p5, p2);
	createSpring(p5, p7);
	
	// right foot to hips
	createSpring(p6, p3);
	createSpring(p6, p8);
	
	// left hip to right hip fro more stability
	createSpring(p7, p8);
	
}

void creature::update() {
	

	// calculate the the muscle length depending on if it's a big guy or little guy
	float muscleLength = size < 75 ? 7 : 15;
		
	
	for (int i = 10; i < 14; i++) {
		// set spring distance to rest length + however much we're stretching
		// multiply the sine offset so there's some diversity in hop rate
		springs[i].distance = springs[i].restLength + muscleLength * sin(ofGetElapsedTimef()*8 * sinOffset);
	}
	
	
	for (int i = 0; i < particles.size(); i++){
		particles[i]->resetForce();
	}
	
	for (int i = 0; i < particles.size(); i++){
		particles[i]->addForce(0,0.1f);
		particles[i]->addRepulsionForce(mouseX, mouseY, 75, 3);
	}
	
	for (int i = 0; i < springs.size(); i++){
		springs[i].update();
	}
	
	
	for (int i = 0; i < particles.size(); i++){
		particles[i]->bounceOffWalls();
		particles[i]->addDampingForce();
		particles[i]->update();
	}
	
}

void creature::draw() {
	
	ofSetColor(color);
	ofFill();
	
	//	for (int i = 0; i < particles.size(); i++){
	//		particles[i]->draw();
	//	}
	//
	//	for (int i = 0; i < springs.size(); i++){
	//		springs[i].draw();
	//	}
	
	// draw the whole thing as one shape so that you can tell
	// when the feet are inside the body. kind of cute!
	
	//	ofBeginShape();
	//	
	//	ofVertex(particles[0]->pos.x, particles[0]->pos.y);
	//	ofVertex(particles[1]->pos.x, particles[1]->pos.y);
	//	
	//	ofVertex(particles[4]->pos.x, particles[4]->pos.y);
	//	
	//	ofVertex(particles[6]->pos.x, particles[6]->pos.y);
	//	ofVertex(particles[7]->pos.x, particles[7]->pos.y);
	//	
	//	ofVertex(particles[5]->pos.x, particles[5]->pos.y);
	//	
	//	ofVertex(particles[2]->pos.x, particles[2]->pos.y);
	//	ofVertex(particles[3]->pos.x, particles[3]->pos.y);
	//	
	//	ofVertex(particles[0]->pos.x, particles[0]->pos.y);
	//	
	//	ofEndShape();
	
	
	// different method for drawing the creature with different
	// shapes for body and legs. i like it a bit more.
	ofBeginShape();
	ofVertex(particles[0]->pos.x, particles[0]->pos.y);
	ofVertex(particles[1]->pos.x, particles[1]->pos.y);
	ofVertex(particles[2]->pos.x, particles[2]->pos.y);
	ofVertex(particles[3]->pos.x, particles[3]->pos.y);
	ofEndShape();
	
	ofBeginShape();
	ofVertex(particles[1]->pos.x, particles[1]->pos.y);
	ofVertex(particles[4]->pos.x, particles[4]->pos.y);
	ofVertex(particles[6]->pos.x, particles[6]->pos.y);
	ofEndShape();

	ofBeginShape();
	ofVertex(particles[2]->pos.x, particles[2]->pos.y);
	ofVertex(particles[5]->pos.x, particles[5]->pos.y);
	ofVertex(particles[7]->pos.x, particles[7]->pos.y);
	ofEndShape();
	

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
	
	spring s;
	
	s.restLength	= (p1->pos - p2->pos).length();
	s.springiness	= 0.4f;
	s.particleA		= p1;
	s.particleB		= p2;
	
	s.distance = s.restLength;
	
	springs.push_back(s);
}


void creature::repelMouse(float x, float y) {
	mouseX = x;
	mouseY = y;
}