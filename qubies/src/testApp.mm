#include "testApp.h"

// GLOBALS

// Vars for whether a finger is down
vector <bool> touchStatus;
vector <float> touchX, touchY;

//--------------------------------------------------------------
void testApp::setup() {	
	// initialize the accelerometer
	ofxAccelerometer.setup();
	
	//If you want a landscape oreintation 
	iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);

	// Set background & program stuff
	ofBackground(255);
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofEnableAlphaBlending();
	ofEnableSmoothing();
	//ofSetCircleResolution(60);
	//ofSetBackgroundAuto(false);

	// Font stuff
	ofTrueTypeFont::setGlobalDpi(72);
	qbicle.loadFont("qbicle4.ttf", 128, true, false);
	qbicle.setLineHeight(18.0f);
	qbicle.setLetterSpacing(1.037);
	
	code64.loadFont("code_bold.otf", 64, true, false);
	code64.setLineHeight(18.0f);
	code64.setLetterSpacing(1.037);

	code32.loadFont("code_bold.otf", 32, true, false);
	code32.setLineHeight(18.0f);
	code32.setLetterSpacing(1.037);
	
	gameStarted = false;
	gameRunning = false;
	
	// Level stuff
	levelNumber = 1;
	//beginLevel(levelNumber);
	
}


//--------------------------------------------------------------
void testApp::beginLevel(int levelNumber) {
	
	//levelNumber = 1;
	gameStarted = true;
	gameRunning = true;
	levelCompleted = false;
	qubieKillCount = 0;

	// ground stuff
	ground.clear();
	groundXVals.clear();
	groundYVals.clear();
	
	ground.addVertex(0, ofGetHeight() * .93);
	groundXVals.push_back(0);
	groundYVals.push_back(ofGetHeight() * .93);
	
	for (float i = 0; i < ofGetWidth()/100; i += 0.1) {
		ground.curveTo(i*100, ofGetHeight() * .93 + ofNoise(i)*50);
		groundXVals.push_back(i*100);
		groundYVals.push_back(ofGetHeight() * .93 + ofNoise(i)*50);
	}
	
	ground.curveTo(ofGetWidth(), ofGetHeight() * .93);
	groundXVals.push_back(ofGetWidth());
	groundYVals.push_back(ofGetHeight() * .93);
	
	// Pick a basis color & number of colors for the creatures
	colorRoot = 120; // ofRandom(255);
	colorCount = levelNumber;
	colorSpread = max(30 - (10 * levelNumber), 10);
	colorIterator = 0;
	
	int creatureCount = 3 + ((levelNumber - 1) * 2);
	
	// creature a bunch of creatures
	creatures.clear();
	
	for (int i = 0; i < creatureCount; i++) {
		generateCreature();
	}
	
	// timer stuff
	creatureLastTime = ofGetElapsedTimef();
	creatureDuration = max(5 - levelNumber + 1, 1);
}

//--------------------------------------------------------------
void testApp::generateCreature() {
	
	float size = ofRandom(30, 35);
	
	// give them random fun, bright, semi-transparent colors
	// with the infamous Matt Felsen triadic color palette algorithm
	float hue = fmod(colorRoot + colorIterator++ % colorCount * (255/colorCount) + ofRandom(colorSpread), 255);
	ofColor col = ofColor::fromHsb(hue, 200, 200, 200);

	creature c;
	c.setup(col, size, ground);
	creatures.push_back(c);

}

//--------------------------------------------------------------
void testApp::update() {

	// If the game is currently running, do some creature-related
	// stuff (create new ones, remove dead ones, etc.)
	if (gameRunning) {
	
		// Use timer to check if we should create a new creature
		float timeDiff = ofGetElapsedTimef() - creatureLastTime;

		if (timeDiff > creatureDuration) {
			creatureLastTime = ofGetElapsedTimef();
			generateCreature();
		}
		
		// Update all the creatures and check if they're dead
		for (int i = 0; i < creatures.size(); i++) {
			creatures[i].update();
			
			if (creatures[i].dead) {
				creatures.erase(creatures.begin() + i);
				qubieKillCount++;
			}
		}
		
	}

	// If there are no more creatures, check if we just finished a level
	// or if we are ready to start the next level yet
	if (creatures.size() == 0 && gameStarted) {
		if (gameRunning) {
			levelCompleted = true;
			gameRunning = false;
			
			gameLastTime = ofGetElapsedTimef();
			gameDuration = 5;
		} else {
			float timeDiff = ofGetElapsedTimef() - gameLastTime;
			
			if (timeDiff > gameDuration) {
				beginLevel(++levelNumber);
			}
		}
	}
	
}

//--------------------------------------------------------------
void testApp::draw() {

	ofColor start, end;

	// Set black for text
	ofSetColor(0);
	
	if (!gameStarted) {
		start = ofColor(255, 255, 255);
		end = ofColor(225, 225, 225);
		
		ofBackgroundGradient(start, end, OF_GRADIENT_CIRCULAR);

		// Draw title
		string qubieString = "QUBIES";
		float qubieWidth = qbicle.stringWidth(qubieString);
		
		qbicle.drawString(qubieString, ofGetWidth()/2 - qubieWidth/2, 300);

		// Draw medium text for preparedness text
		string welcomeString = "Knock the qubies off the top of the screen!\n\nUse your fingers to push them from below.";
		float welcomeWidth = code32.stringWidth(welcomeString);
		float welcomeHeight = code32.stringHeight(welcomeString);
		
		code32.drawString(welcomeString, ofGetWidth()/2 - welcomeWidth/2, ofGetHeight()/2 + welcomeHeight);
		
	}
	
	// Draw backgrounds and informational text
	if (levelCompleted) {
		
		// Draw background gradient
		start = ofColor(255, 255, 255);
		end = ofColor::fromHsb(127, 25, 200);
		
		ofBackgroundGradient(start, end, OF_GRADIENT_CIRCULAR);

		
		// Draw large text for level completion
		char completeString[1024];
		sprintf(completeString, "LEVEL %i COMPLETE!", levelNumber);

		float completeWidth = code64.stringWidth(completeString);
		float completeHeight = code64.stringHeight(completeString);

		code64.drawString(completeString, ofGetWidth()/2 - completeWidth/2, ofGetHeight()/2 - completeHeight/2);
		
		// Draw medium text for preparedness text
		string prepareString = "Get ready for the next level";
		float prepareWidth = code32.stringWidth(prepareString);
		float prepareHeight = code32.stringHeight(prepareString);
		
		code32.drawString(prepareString, ofGetWidth()/2 - prepareWidth/2, ofGetHeight()/2 - prepareHeight/2 + completeHeight);

	}
	
	if (gameRunning) {	
		start = ofColor(255, 255, 255);
		end = ofColor(200, 200, 200);
		
		ofBackgroundGradient(start, end, OF_GRADIENT_CIRCULAR);
		
		// Draw text for level number
		char levelString[1024];
		sprintf(levelString, "LEVEL %i", levelNumber);
		
		code32.drawString(levelString, 20, 40);

		// Draw text for qubie kill count
		string qubieString = "QUBIES KILLED";
		float qubieWidth = code32.stringWidth(qubieString);

		code32.drawString(qubieString, ofGetWidth() - qubieWidth - 20, 40);

		char qubieCount[1024];
		sprintf(qubieCount, "%i", qubieKillCount);
		float qubieKillWidth = code32.stringWidth(qubieCount);
		float qubieKillPosition = ofGetWidth() - qubieWidth - 20 - qubieKillWidth - 10;
		
		code32.drawString(qubieCount, qubieKillPosition, 40);

		
		//ofSetColor(0);
		//ground.draw();
		
		
		// Finally, draw all the little qubies
		for (int i = 0; i < creatures.size(); i++) {
			creatures[i].draw();
		}
		
	}

	
//	for (int i = 0; i < touchStatus.size(); i++) {
//		if (touchStatus[i]) {
//			ofSetColor(ofColor::fromHsb(i*30, 200, 200));
//			ofFill();
//			ofCircle(touchX[i], touchY[i], 50);
//		}
//	}
	
}

//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){

	//cout << "DOWN: Size: " << touchStatus.size() << ", ID: " << touch.id << endl;

	if (!gameStarted) {
		beginLevel(levelNumber);
	}
	
	if (touch.id < levelNumber) {
		if (touchStatus.size() <= touch.id) {
			touchStatus.push_back(true);
			touchX.push_back(touch.x);
			touchY.push_back(touch.y);
		} else {
			touchStatus[touch.id] = true;
			touchX[touch.id] = touch.x;
			touchY[touch.id] = touch.y;

		}
	}

	// Reset if we have 10 fingers on the screen (the "secret reset gesture")
//	if (touch.id == 9) {
//		beginLevel(levelNumber);
//	}
	
	//cout << "DOWN: New size: " << touchStatus.size() << endl;
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
	
	//cout << "MOVED: Size: " << touchStatus.size() << ", ID: " << touch.id << endl;
	
	if (touch.id < levelNumber) {
		touchX[touch.id] = touch.x;
		touchY[touch.id] = touch.y;
	}

	/*
	for (int i = 0; i < creatures.size(); i++) {
		creatures[i].repelMouse(touch.x, touch.y);
	}
	*/

}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){

	//cout << "UP: Size: " << touchStatus.size() << ", ID: " << touch.id << endl;
	
	/*
	if (touchStatus.size() == 0) {
		touchStatus.clear();
		touchX.clear();
		touchY.clear();
	} else {
		touchStatus.erase(touchStatus.begin() + touch.id);
		touchX.erase(touchX.begin() + touch.id);
		touchY.erase(touchY.begin() + touch.id);
	}
	*/
	
	if (touch.id < levelNumber) {
		touchStatus[touch.id] = false;
	}
	
	//cout << "UP: New size: " << touchStatus.size() << endl;
}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){
	for (int i = 0; i < creatures.size(); i++) {
		creatures[i].shakeUp();
	}
}

//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void testApp::lostFocus(){

}

//--------------------------------------------------------------
void testApp::gotFocus(){

}

//--------------------------------------------------------------
void testApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){

}

