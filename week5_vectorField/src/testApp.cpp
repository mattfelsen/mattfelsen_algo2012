#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);

	VF.setupField(50, 35,ofGetWidth(), ofGetHeight());
	//VF.randomizeField(6.5);
	
	drawField = true;

	for (int i = 0; i < 1000; i++){
		particle myParticle;
		myParticle.setInitialCondition(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0,0);
		particles.push_back(myParticle);
	}
}

//--------------------------------------------------------------
void testApp::update(){
	//VF.fadeField(0.99f);

	for (int i = 0; i < particles.size(); i++){
		particles[i].resetForce();
		
		// get the force from the vector field:
		ofVec2f frc;
		frc = VF.getForceFromPos(particles[i].pos.x, particles[i].pos.y);
		particles[i].addForce(frc.x, frc.y);
		particles[i].addDampingForce();
		particles[i].update();
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofSetColor(0,0,0);
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].draw();
	}
	
	ofEnableAlphaBlending();
	ofSetColor(0,130,130, 200);

	ofDisableAlphaBlending();

	if (drawField)
		VF.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	if (key == ' ')
		drawField = !drawField;

	if (key == 'r') {
		particles.clear();
		for (int i = 0; i < 1000; i++){
			particle myParticle;
			myParticle.setInitialCondition(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0,0);
			particles.push_back(myParticle);
		}
	}

	if (key == 'c')
		VF.clear();
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){ 
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	prevMouseX = x;
	prevMouseY = y;
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

	float dx = x - prevMouseX;
	float dy = y - prevMouseY;
	
	//myParticle.setInitialCondition(x,y, dx*0.3,dy*0.3);

	VF.addMouseForce(x, y, dx, dy);
	
//	if (button == 0){
//		VF.addOutwardCircle(x,y, 100, 0.3) ;
//	} else {
//		VF.addCounterClockwiseCircle(x, y, 200, 0.3);
//	}
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
}
