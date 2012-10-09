#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofSetVerticalSync(true);
	ofSetCircleResolution(50);
	
	firework fw;
	fw.setup(300, 300);
	fireworks.push_back(fw);

}

//--------------------------------------------------------------
void testApp::update(){

	for (int i = 0; i < fireworks.size(); i++){

		printf("elapsed: %f, lifetime: %f, born: %f\n", fireworks[i].elapsed, fireworks[i].lifetime, fireworks[i].born);
		
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