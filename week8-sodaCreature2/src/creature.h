//
//  creature.h
//  muscles
//
//  Created by Matt on 11/18/12.
//
//

#ifndef __muscles__creature__
#define __muscles__creature__

#include <iostream>
#include "ofMain.h"
#include "particle.h"
#include "spring.h"

class creature {

public:
	
	void setup(ofColor color, float size);
	void update();
	void draw();
	
	void createSpring(particle * p1, particle * p2);
	void repelMouse(float x, float y);

	ofPoint pos;
	float size;

	ofColor color;
	
	float sinOffset;
	
	vector <particle * > particles;
	vector <spring> springs;
	
	float mouseX, mouseY;
	
};

#endif /* defined(__muscles__creature__) */
