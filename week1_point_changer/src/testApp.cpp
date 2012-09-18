#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
	// macs by default run on non vertical sync, which can make animation very, very fast
	// this fixes that:
	
	ofSetVerticalSync(true);
	
	// set background:
	
	ofBackground(0, 0, 0);
	
	
	// set the "a" and "b" positions of the rectangle...
	
	myRectangle.posa.x = 0;
	myRectangle.posa.y = 200;
	myRectangle.posb.x = ofGetWidth();
	myRectangle.posb.y = 200;
	
	
	//myRectangle.radiusa = 30;
	//myRectangle.radiusb = 200;
	
	//myRectangle.interpolateByPct(0);	// start at 0 pct
	//pct = 0;							// a variable we can alter...
    
    
    inc = 0.01;
    toggle = true;
}

//--------------------------------------------------------------
void testApp::update(){
    
	//pct = (float) mouseY / (float) ofGetHeight();
	
	//printf("%f \n", pct);
	
	pct += inc;
    pct = fmod(pct, 1);
	
	myRectangle.interpolateByPct(pct);
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
	myRectangle.draw();

    ofDrawBitmapString("pt a: " + ofToString(myRectangle.posa.x) + ", " + ofToString(myRectangle.posa.y), 20, 20);
    ofDrawBitmapString("pt b: " + ofToString(myRectangle.posb.x) + ", " + ofToString(myRectangle.posb.y), 20, 35);
    
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
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    if (toggle) {
        myRectangle.posa.x = x;
        myRectangle.posa.y = y;
    } else {
        myRectangle.posb.x = x;
        myRectangle.posb.y = y;
    }
    
    toggle = !toggle;
    pct = 0;
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