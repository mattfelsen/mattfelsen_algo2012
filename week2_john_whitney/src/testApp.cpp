#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    res = 2000;
 
    ofEnableSmoothing();
    ofSetColor(255);
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    // Scale r to 0-1
    r = (sin(ofGetElapsedTimef() / 20) + 1) / 2;
    
    // Scale R to 100-300
    R = (sin(ofGetElapsedTimef() / 20) + 1) * 100 + 100;
    
    // Scale O to...something. -200 - 600?
    O = (sin(ofGetElapsedTimef() / 3) + 1) * 400 - 200;

}

//--------------------------------------------------------------
void testApp::draw(){

    ofBackground(0);
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    

    float px = 0;
    float py = 0;
    
    for (int i = 0; i < res; i++) {
        //for (int i = 0; i < TWO_PI; i+= 0.1) {
        float theta = ofMap(i, 0, res, 0, TWO_PI);
        
        // Spirographs!
        float x = (R+r)*cos(theta) - (r+O)*cos(((R+r)/r)*theta);
        float y = (R+r)*sin(theta) - (r+O)*sin(((R+r)/r)*theta);
        
        //point (x, y);
        if (px != 0 && py != 0)
            ofLine(x, y, px, py);
        
        px = x;
        py = y;
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

    //r = ofMap(x, 0, ofGetWidth(), 0, 1);
    R = ofMap(y, 0, ofGetHeight(), 100, 200);
    O = ofMap(x+y, 0, ofGetWidth()+ofGetHeight(), 10, 100);
    
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