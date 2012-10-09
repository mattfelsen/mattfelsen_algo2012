//
//  fireworkParticle.cpp
//  week4_fireworks
//
//  Created by Matt on 10/7/12.
//
//

#include "fireworkParticle.h"


fireworkParticle::fireworkParticle() {
	setup(0, 0, 0, 0);
	damping = 0.01f;
}

void fireworkParticle::setup(float px, float py, float vx, float vy) {
    pos.set(px, py);
	vel.set(vx, vy);
	
	theta = ofRandom(TWO_PI);
	subTheta = ofRandom(TWO_PI);
	subThetaSpeed = ofRandom(0.01, 0.1);

}

void fireworkParticle::resetForce() {
    frc.set(0,0);
}

void fireworkParticle::addForce(float x, float y) {
    //frc.x += x;
    //frc.y += y;

	// Assuming y will be a small number (e.g. 0.01 or 0.05)
	// Use linear interpolation to xeno from whatever theta is
	// and get closer to an angle of 3π/2, which points downward
	theta = (1-y) * theta + y * 3 * HALF_PI;
}

void fireworkParticle::addDampingForce() {
    frc.x -= vel.x * damping;
    frc.y -= vel.y * damping;
}

void fireworkParticle::update() {
	vel = vel + frc;
	
	pos.x += vel.x * cos(theta);
	pos.y += vel.y * sin(theta);

	subTheta += subThetaSpeed;

}

void fireworkParticle::draw() {

	ofPushMatrix();
	
	ofTranslate(pos.x, pos.y);
	
	ofRotateZ(subTheta * RAD_TO_DEG);
	ofTranslate(10, 0);
	
	//ofCircle(pos.x, pos.y, 3);
	ofCircle(0, 0, 3);
	
	ofPopMatrix();

}

