#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	for (int i = 0; i < numXenos; i++) {
		things[i].setup(0.1);
	}
}

//--------------------------------------------------------------
void testApp::update(){
	
	for (int i = 0; i < numXenos; i++) {
		things[i].update();
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofBackground(0);
	
	for (int i = 0; i < numXenos; i++) {
		things[i].draw();
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
	
	for (int i = 0; i < numXenos; i++) {
		if (i == 0)
			things[i].setTarget(x, y);
		else
			things[i].setTarget(things[i-1].pos.x, things[i-1].pos.y);
	}
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

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