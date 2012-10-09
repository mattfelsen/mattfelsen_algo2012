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
	float born;
	float elapsed;
	bool exploded;
	ofColor c;
	
	ofPoint pos;
	
	vector <fireworkParticle> particles;
	
	void setup(int x, int y);
	void update();
	void draw();
	
};

#endif /* defined(__week4_fireworks__firework__) */
