//
//  firework.cpp
//  week4_fireworks
//
//  Created by Matt on 10/7/12.
//
//

#include "firework.h"

void firework::setup(int x, int y) {

	currentPos.x = x;
	targetPos = ofPoint(x, y);
	
	exploded = false;
	
	lifetime = 3.5;
	ascendTime = 1.5;
	born = ofGetElapsedTimef();
	
	c = ofColor::fromHsb(ofRandom(255), 200, 225);
	
	particleCount = 700;
	
}

void firework::update() {
	
	elapsed = ofGetElapsedTimef() - born;

	if (elapsed > ascendTime && !exploded) {
		exploded = true;
		explode();
	} else {
		
		float pct = elapsed / ascendTime;
		pct = powf(pct, 0.8);
		currentPos.y = ofGetHeight() * (1-pct) + pct * targetPos.y;
	}
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].resetForce();
		//particles[i].addForce(0, 0.1);
		particles[i].addDampingForce();
		particles[i].update();
	}
	
}

void firework::draw() {

	if (!exploded) {

		float noise = ofNoise(currentPos.x, currentPos.y) * 2;
		ofSetColor(255, 255, 255);
		ofCircle(currentPos.x + noise, currentPos.y, 3);

	} else {

		float pct = elapsed / lifetime;
		pct = powf(pct, 2);
		
		for (int i = 0; i < particles.size(); i++){
			//ofSetColor(255 * (1 - pct));
			ofSetColor(c, 90 * (1 - pct));
			particles[i].draw();
		}
		
	}
	
}

void firework::explode() {
	
	for (int i = 0; i < particleCount; i++){
		fireworkParticle particle;
		float vx = ofRandom(-4,4);
		float vy = ofRandom(-4,4);
		particle.setup(currentPos.x, currentPos.y, vx, vy);
		// more interesting with diversity :)
		// uncomment this:
		//particle.damping = ofRandom(0.01, 0.05);
		particles.push_back(particle);
	}
	
}