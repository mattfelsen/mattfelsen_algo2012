//
//  xenoThing.cpp
//  week1_multiXeno
//
//  Created by Matt on 9/26/12.
//
//

#include "xenoThing.h"

void xenoThing::setup(float speed) {
	
	pos.x = 100;
	pos.y = 100;
	
	w = 50;
	h = 50;
	
	c = ofColor::fromHsb(ofRandom(255), 200, 200);

	this->speed = speed;
}

void xenoThing::update() {

	pos.x = target.x * speed + pos.x * (1 - speed);
	pos.y = target.y * speed + pos.y * (1 - speed);
	
}

void xenoThing::draw() {
	
	ofSetColor(c);
	ofRect(pos.x, pos.y, w, h);
	
}

void xenoThing::setTarget(float x, float y) {

	target.x = x;
	target.y = y;

}