//
//  firework.cpp
//  week4_fireworks
//
//  Created by Matt on 10/7/12.
//
//

#include "firework.h"

void firework::setup(int x, int y) {

	lifetime = 3;
	born = ofGetElapsedTimef();
	
	int fireworkParticles = 700;
	
	for (int i = 0; i < fireworkParticles; i++){
		fireworkParticle particle;
		float vx = ofRandom(-4,4);
		float vy = ofRandom(-4,4);
		particle.setup(x, y, vx, vy);
		// more interesting with diversity :)
		// uncomment this:
		//myParticle.damping = ofRandom(0.01, 0.05);
		particles.push_back(particle);
	}
	
}

void firework::update() {
	
	elapsed = ofGetElapsedTimef() - born;
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].resetForce();
		//particles[i].addForce(0, 0.01);
		particles[i].addDampingForce();
		particles[i].update();
	}
	
}

void firework::draw() {

	float pct = elapsed / lifetime;
	pct = powf(pct, 2);
	
	for (int i = 0; i < particles.size(); i++){
		ofSetColor(255 * (1 - pct));
		particles[i].draw();
	}
	
}