#pragma once

#include "ofMain.h"

#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxAccelerometer.h"

#include "creature.h"

class testApp : public ofxiPhoneApp{

public:
	void setup();
	void update();
	void draw();
	void exit();

	void touchDown(ofTouchEventArgs & touch);
	void touchMoved(ofTouchEventArgs & touch);
	void touchUp(ofTouchEventArgs & touch);
	void touchDoubleTap(ofTouchEventArgs & touch);
	void touchCancelled(ofTouchEventArgs & touch);

	void lostFocus();
	void gotFocus();
	void gotMemoryWarning();
	void deviceOrientationChanged(int newOrientation);

	void beginLevel(int levelNumber);
	void generateCreature();
	
	// List of creatures
	vector <creature> creatures;

	// Color-related
	int colorRoot;
	int colorCount;
	int colorSpread;
	int colorIterator;
	
	// Variables for timer
	float lastTime, duration;
	float gameLastTime;
	float gameDuration;
	float creatureLastTime;
	float creatureDuration;
	
	// Variables for levels
	bool gameStarted;
	bool gameRunning;
	
	int levelNumber;
	bool levelCompleted;
	
	int qubieKillCount;
	
	vector <float> groundXVals;
	vector <float> groundYVals;
	ofPolyline ground;
	
	// Fonts
	ofTrueTypeFont qbicle;
	ofTrueTypeFont code64;
	ofTrueTypeFont code32;


};


