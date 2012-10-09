#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofSetVerticalSync(true);
	ofEnableSmoothing();
	ofBackground(0);
	ofSetCircleResolution(50);
	ofSetRectMode(OF_RECTMODE_CENTER);
	
	hueTracker = -30;
	shapeTracker = -1;
	shapeCount = 1;
	
	recorder r;
	recorders.push_back(r);
	recorders[0].setup(hueTracker += 30, shapeTracker++);
	
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

	for (int i = 0; i < recorders.size(); i++) {
		recorders[i].draw();
		
		if (recorders[i].drawable()) {
			recorders[i].drawShape();
		}
	}
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	// c clears all paths
	if (key == 99)
		recorders.clear();
	
	// d deletes last path
	if (key == 100)
		recorders.pop_back();

	// 1-9 set shapeCount to key number
	if (49 <= key && key <= 57) {
		shapeCount = key - 48;
		
		for (int i = 0; i < recorders.size(); i++) {
			recorders[i].setShapeCount(shapeCount);
		}
	}
	
	// p toggles showing the paths
	if (key == 112) {
		for (int i = 0; i < recorders.size(); i++) {
			recorders[i].showPath = !recorders[i].showPath;
		}
	}
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

	recorders[recorders.size()-1].add(x, y);
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

	recorder r;
	recorders.push_back(r);
	recorders[recorders.size()-1].setup(hueTracker += 30, shapeTracker++);
	recorders[recorders.size()-1].setShapeCount(shapeCount);
	recorders[recorders.size()-1].start(x, y);
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

	recorders[recorders.size()-1].end();
	
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