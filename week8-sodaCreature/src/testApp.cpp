#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	
	
	ofBackground(255);
	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofEnableAlphaBlending();
	ofEnableSmoothing();
	
	int basisColor = ofRandom(255);
	int colors = 3;
	
	creatures.clear();
	
	// creature a bunch of creatures
	for (int i = 0; i < 50; i++) {
		creature c;
		float size;
		
		// make a few bigger guys and then a bunch of smaller cuties
		if (i < 3)
			size = ofRandom(75, 100);
		else
			size = ofRandom(25, 30);
		
		// give them random fun, bright, semi-transparent colors
		// with the infamous Matt Felsen triadic color palette algorithm
		float hue = fmod(basisColor + i%colors * (255/colors) + ofRandom(20), 255);
		ofColor col = ofColor::fromHsb(hue, 200, 200, 200);
		c.setup(col, size);

		creatures.push_back(c);
	}
}

//--------------------------------------------------------------
void testApp::update(){

	// on every frame 
	// we reset the forces
	// add in any forces on the particle
	// perfom damping and
	// then update
	
	for (int i = 0; i < creatures.size(); i++)
		creatures[i].update();
}

//--------------------------------------------------------------
void testApp::draw(){
	
	for (int i = 0; i < creatures.size(); i++)
		creatures[i].draw();
	
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	if (key == ' ')
		setup();
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){ 
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
//	particles[0]->pos.set(mouseX, mouseY);
	/*particles.erase(particles.begin());
	particle myParticle;
	myParticle.setInitialCondition(x,y,0,0);
	particles.push_back(myParticle);*/
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
//	particles[0]->bFixed = true;
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
	
//	particles[0]->bFixed = false;
}

