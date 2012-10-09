#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofSetVerticalSync(true);
	ofSetCircleResolution(50);
	ofEnableAlphaBlending();

}

//--------------------------------------------------------------
void testApp::update(){

	if (ofGetFrameNum() % 20 == 0) {
		float x = ofMap(sin(ofGetElapsedTimef()*3), -1, 1, 100, ofGetWidth() - 100);
		
		firework fw;
		fw.setup(x, ofRandom(100, 350));
		fireworks.push_back(fw);
	}
	
	
	for (int i = 0; i < fireworks.size(); i++){
		
		if (fireworks[i].elapsed > fireworks[i].lifetime)
			fireworks.erase(fireworks.begin()+i);
		else
			fireworks[i].update();
	}
	
}

//--------------------------------------------------------------
void testApp::draw(){

	ofBackground(0);
	
	for (int i = 0; i < fireworks.size(); i++){
		fireworks[i].draw();
	}
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

	firework fw;
	fw.setup(x, y);
	fireworks.push_back(fw);
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}