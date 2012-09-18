//
//  rectangle.h
//  week1_point_changer
//
//  Created by Matt on 9/18/12.
//
//

#ifndef __week1_point_changer__rectangle__
#define __week1_point_changer__rectangle__

#include <iostream>

#include "ofMain.h"

class rectangle {
    
public:
	
    rectangle();
	
    void draw();
    void interpolateByPct(float myPct);
    
    ofPoint		pos;
    ofPoint		posa;
    ofPoint		posb;
    float		pct;	// what pct are we between "a" and "b"
	
	
    float		radius;
	
    float		radiusa;
    float		radiusb;
    
    float       w;
    float       h;
    
};

#endif /* defined(__week1_point_changer__rectangle__) */
