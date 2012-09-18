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
    
    
    //inc = 0.003;  // slowest
    inc = 0.036;    // fastest
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

    float ppf = inc * ofGetWidth();
    float pps = ppf * 60;           // Assuming fixed 60 fps
    float ips = pps / 113;          // MBP13 display is 113 pixel sper inch
    float mps = ips / 12 / 5280;    // 12" per foot, 5280' per mile
    float mph = mps / 3600;         // 60s per m, 60m per h
    
	myRectangle.draw();
	
	ofSetColor(255,255,255);
	ofDrawBitmapString("Percent: " + ofToString(pct), 20, 20);
    ofDrawBitmapString("Increment: " + ofToString(inc) + " / " + ofToString(inc * 100) + "%", 20, 35);
    ofDrawBitmapString("Pixels per frame: " + ofToString(ppf), 20, 50);
    ofDrawBitmapString("Pixels per Second: " + ofToString(pps), 20, 65);
    ofDrawBitmapString("Inches per Second: " + ofToString(ips), 20, 80);
    ofDrawBitmapString("Miles per Second: " + ofToString(mps), 20, 95);
    ofDrawBitmapString("Miles per Hour: " + ofToString(mph), 20, 110);

    
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