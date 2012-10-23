#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	

	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofEnableAlphaBlending();
	
	for (int i = 0; i < 700; i++){
		particle p;
		p.setInitialCondition(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), 0, 0);
		p.damping = ofRandom(0.07, 0.08);
		particles.push_back(p);
	}

	VF.setupField(ofGetWidth()/10, ofGetHeight()/10,ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void testApp::update(){	
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].resetForce();
	}

	for (int i = 0; i < particles.size(); i++){
		
		particles[i].addAttractionForce(-500, particles[i].initialY, 2000, 2);
		//particles[i].addRepulsionForce(mouseX, mouseY, 125, 2.5);

		// get the force from the vector field:
		ofVec2f frc;
		frc = VF.getForceFromPos(particles[i].pos.x, particles[i].pos.y);
		particles[i].addForce(frc.x, frc.y);
		
		for (int j = 0; j < i; j++){
			particles[i].addRepulsionForce(particles[j], 50, 0.4);
		}
	}

	for (int i = 0; i < particles.size(); i++){
		//particles[i].addCounterClockwiseForce(mouseX, mouseY, 1000, 0.1);
		//particles[i].addClockwiseForce(mouseX, mouseY, 200, 1);
		
		particles[i].addDampingForce();
		particles[i].update();
		
		if (particles[i].pos.x < 0) {
			particles[i].setInitialCondition(ofGetWidth(), ofRandom(ofGetHeight()), -10, 0);
		}
	}

	VF.fadeField(0.97f);
	
}

//--------------------------------------------------------------
void testApp::draw(){

	ofBackground(0);

	ofSetColor(0,130,130, 200);
	//VF.draw();
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].draw();
	}

}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){ 
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
		VF.addOutwardCircle(x,y, 150, 2.5) ;
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(){
}
