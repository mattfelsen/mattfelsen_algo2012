#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetColor(255);
    ofNoFill();
    
    ofSetCircleResolution(100);
    
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(0);
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    
//    ofLine(-500, 0, 0, 500, 0, 0);
//    ofLine(0, -500, 0, 0, 500, 0);
//    ofLine(0, 0, -500, 0, 0, 500);
    
    float theta = 0;
    int z = 0;
    
    for (int i = 0; i < 90; i++) {
        theta += 0.05;
        
        int size = ofMap(i, 0, 50, 30, 200);
        int dist = ofMap(i, 0, 100, 0, 300);

        float x = dist * cos(theta);
        float y = dist * -sin(theta);
        
        z += 2;
        
        ofPushMatrix();
        ofRotateY(2);
        ofEllipse(x, z, y, size, size);
        ofPopMatrix();
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