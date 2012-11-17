#include "particle.h"
#include "ofMain.h"


//------------------------------------------------------------
particle::particle(){
	setInitialCondition(0,0,0,0);
	damping = 0.09f;
}

//------------------------------------------------------------
void particle::resetForce(){
    // we reset the forces every frame
    frc.set(0,0);
}

//------------------------------------------------------------
void particle::addForce(float x, float y){
    // add in a force in X and Y for this frame.
    frc.x = frc.x + x;
    frc.y = frc.y + y;
}

//------------------------------------------------------------
void particle::addDampingForce(){
	
	// the usual way to write this is  vel *= 0.99
	// basically, subtract some part of the velocity
	// damping is a force operating in the oposite direction of the
	// velocity vector
	
    frc.x = frc.x - vel.x * damping;
    frc.y = frc.y - vel.y * damping;
}


//------------------------------------------------------------
void particle::addRepulsionForce( float px, float py, float radius, float strength){
	
	
	ofVec2f posOfForce;
	posOfForce.set(px, py);
	
	ofVec2f diff = pos - posOfForce;
	
	if (diff.length() < radius){
		float pct = 1 - (diff.length() / radius);
		diff.normalize();
		frc.x += diff.x * pct * strength;
		frc.y += diff.y * pct * strength;
	}
	
}

//------------------------------------------------------------
void particle::addRepulsionForce(particle &p, float radius, float scale){
	
	// ----------- (1) make a vector of where this particle p is:
	ofVec2f posOfForce;
	posOfForce.set(p.pos.x,p.pos.y);
	
	// ----------- (2) calculate the difference & length
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x + diff.x * scale * pct;
        frc.y = frc.y + diff.y * scale * pct;
		p.frc.x = p.frc.x - diff.x * scale * pct;
        p.frc.y = p.frc.y - diff.y * scale * pct;
    }
}

//------------------------------------------------------------
void particle::addAttractionForce( float px, float py, float radius, float strength){
	
	
	ofVec2f posOfForce;
	posOfForce.set(px, py);
	
	ofVec2f diff = pos - posOfForce;
	
	if (diff.length() < radius){
		float pct = 1 - (diff.length() / radius);
		diff.normalize();
		frc.x -= diff.x * pct * strength;
		frc.y -= diff.y * pct * strength;
	}
	
}


//------------------------------------------------------------
void particle::addClockwiseForce( float px, float py, float radius, float strength){
	
	
	ofVec2f posOfForce;
	posOfForce.set(px, py);
	
	ofVec2f diff = pos - posOfForce;
	
	if (diff.length() < radius){
		float pct = 1 - (diff.length() / radius);
		diff.normalize();
		frc.x -= diff.y * pct * strength;
		frc.y += diff.x * pct * strength;
	}
	
}

//------------------------------------------------------------
void particle::addCounterClockwiseForce( float px, float py, float radius, float strength){
	
	
	ofVec2f posOfForce;
	posOfForce.set(px, py);
	
	ofVec2f diff = pos - posOfForce;
	
	if (diff.length() < radius){
		float pct = 1 - (diff.length() / radius);
		diff.normalize();
		frc.x += diff.y * pct * strength;
		frc.y -= diff.x * pct * strength;
	}
	
}



//------------------------------------------------------------
void particle::setInitialCondition(float px, float py, float vx, float vy){
    pos.set(px,py);
	vel.set(vx,vy);
	
	initialY = py;
	prevPos = pos;
	
	magic = false;
}

//------------------------------------------------------------
void particle::update(){
	prevPos = pos;
	
	vel = vel + frc;
	pos = pos + vel;
}

//------------------------------------------------------------
void particle::draw(){
	
	float displacement = abs(initialY - pos.y);
	float hue = ofMap(powf(displacement, 1.5), 0, 255, 120, 160);
	c = ofColor::fromHsb(hue, powf(displacement, 2), 255);
	ofSetColor(c);
	
    //ofCircle(pos.x, pos.y, 2);
	ofSetLineWidth(1.5);
	ofLine(pos.x, pos.y, prevPos.x+5, prevPos.y);
	
}

