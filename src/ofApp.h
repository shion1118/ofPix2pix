#pragma once

#include "ofMain.h"
#include "pix2pix.hpp"
#include "palette.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    protected:
        Pix2pix p2p;
        Palette palette;
        ofFbo fbo;
        ofFloatImage img_input;
        ofFloatImage img_output;
        ofVec2f input_range = {-1, 1};
        ofVec2f output_range = {-1, 1};
    
        void drawImage(ofImage img, int x=0, int y=0);
        void drawMessage(int x=0, int y=0);
};
