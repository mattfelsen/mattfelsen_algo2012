//
//  fireworkParticle.h
//  week4_fireworks
//
//  Created by Matt on 10/7/12.
//
//

#ifndef __week4_fireworks__fireworkParticle__
#define __week4_fireworks__fireworkParticle__

#include <iostream>
#include "ofMain.h"

class fireworkParticle {
	
public:
	
	ofPoint pos;
	ofPoint	vel;
	ofPoint frc;

	float theta;
	float subTheta;
	float subThetaSpeed;
	float damping;
	
	fireworkParticle();
	
	void setup(float px, float py, float vx, float vy);
	void resetForce();
	void addForce(float x, float y);
	void addDampingForce();
	void update();
	void draw();
	
};


#endif /* defined(__week4_fireworks__fireworkParticle__) */
