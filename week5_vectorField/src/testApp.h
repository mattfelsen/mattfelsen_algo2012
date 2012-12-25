#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "vectorField.h"
#include "particle.h"

class testApp : public ofSimpleApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed  (int key);
		void keyReleased (int key);
		
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();
		
		vector <particle> particles;
		vectorField VF;
		bool drawField;

		float prevMouseX;
		float prevMouseY;
};

#endif
	
