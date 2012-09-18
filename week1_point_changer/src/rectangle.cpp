//
//  rectangle.cpp
//  week1_point_changer
//
//  Created by Matt on 9/18/12.
//
//

#include "rectangle.h"

//------------------------------------------------------------------
rectangle::rectangle(){
    w = 30;
    h = w;
}

//------------------------------------------------------------------
void rectangle::draw() {
	ofFill();
	ofSetRectMode(OF_RECTMODE_CENTER); // center around the position
    ofSetColor(255, 255, 255);
    ofRect(pos.x, pos.y, w, h);
}


//------------------------------------------------------------------
void rectangle::interpolateByPct(float myPct){
	pct = myPct;
	
	pos.x = (1-pct) * posa.x + (pct) * posb.x;
	pos.y = (1-pct) * posa.y + (pct) * posb.y;
	
	radius = (1-pct) * radiusa + (pct) * radiusb;
	
}