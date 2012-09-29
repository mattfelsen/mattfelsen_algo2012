//
//  xenoThing.h
//  week1_multiXeno
//
//  Created by Matt on 9/26/12.
//
//

#ifndef __week1_multiXeno__xenoThing__
#define __week1_multiXeno__xenoThing__

#include <iostream>
#include "ofMain.h"


class xenoThing {
    
public:
    void setup(float speed);
    void update();
    void draw();
	void setTarget(float x, float y);
    
	int w, h;
	ofColor c;
	
	ofPoint pos;
	ofPoint target;
	
	float speed;
};

#endif /* defined(__week1_multiXeno__xenoThing__) */
