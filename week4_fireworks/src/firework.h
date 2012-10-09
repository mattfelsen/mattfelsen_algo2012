//
//  firework.h
//  week4_fireworks
//
//  Created by Matt on 10/7/12.
//
//

#ifndef __week4_fireworks__firework__
#define __week4_fireworks__firework__

#include <iostream>
#include "ofMain.h"
#include "fireworkParticle.h"

class firework {

public:
	
	float lifetime;
	float ascendTime;

	float born;
	float elapsed;
	
	bool exploded;

	ofColor c;
	int particleCount;
	
	ofPoint currentPos;
	ofPoint targetPos;
	
	vector <fireworkParticle> particles;
	
	void setup(int x, int y);
	void update();
	void draw();
	
	void explode();
	
};

#endif /* defined(__week4_fireworks__firework__) */
