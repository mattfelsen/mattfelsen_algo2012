#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	
	
	ofBackground(255);
	ofSetBackgroundAuto(false);
	ofEnableAlphaBlending();
	
	ofSetVerticalSync(true);
	//ofSetFrameRate(60);
	
	
	for (int i = 0; i < 2; i++){
		particle myParticle;
		myParticle.setInitialCondition(ofRandom(500,550),ofRandom(500,550),0,0);
		particles.push_back(myParticle);
	}
	
	for (int i = 0; i < (particles.size()-1); i++){
		spring mySpring;
		mySpring.distance		= 50;
		mySpring.springiness	= 0.04f;
		mySpring.particleA = & (particles[i]);
		mySpring.particleB = & (particles[(i+1)%particles.size()]);
		springs.push_back(mySpring);
	}
	
	//particles[particles.size()-1].bFixed = true;
	bDrawing = false;
	
}

//--------------------------------------------------------------
void testApp::update(){

	// on every frame 
	// we reset the forces
	// add in any forces on the particle
	// perfom damping and
	// then update
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].resetForce();
	}
	
	
	for (int i = 0; i < particles.size(); i++){
		//particles[i].addForce(0,0.1);
	}
	 
	
	for (int i = 0; i < springs.size(); i++){
		springs[i].update();
	}
	
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].addDampingForce();
		particles[i].update();
	}
	
	trail.push_back(particles[3].pos);
	if (trail.size() > 150){
		trail.erase(trail.begin());	
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	
	if (!bDrawing)
		return;

	ofSetColor(ofColor::fromHsb(ofGetElapsedTimeMillis() / 5 % 255, 200, 225, 200));
	ofSetLineWidth(3);
	
//	for (int i = 0; i < particles.size(); i++){
//		particles[i].draw();
//	}
	
	for (int i = 0; i < springs.size(); i++){
		springs[i].draw();
	}
	
	ofNoFill();
	ofBeginShape();
	for (int i = 0; i < trail.size(); i++){
		ofVertex(trail[i].x, trail[i].y);
	}
	ofEndShape();

}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
	switch (key){
			
		case ' ':
			ofBackground(255);
	}
	
	
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){ 
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	particles[0].pos.set(mouseX, mouseY);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	particles[0].bFixed = true;
	bDrawing = true;
	
	for (int i = 0; i < particles.size(); i++) {
		particles[i].pos.set(mouseX, mouseY);
	}
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
	particles[0].bFixed = false;
	bDrawing = false;
}

