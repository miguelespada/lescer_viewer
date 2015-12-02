#pragma once

#include "ofMain.h"
#include "app.h"
#include "OscAdapter.h"
#include "gui.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);

    
        App app;
        OscAdapter *osc;
        Gui *gui;
    
//    Arduino *arduino;
    
    
    ofxFloatSlider timeCount;
    ofxIntSlider nivel;
    ofxButton startTimeGame;
    ofxButton startFruitGame;
    ofxButton calibrate;
    ofxButton clear;
    
    void startTimeGamePressed();
    void startFruitGamePressed();
    
    void calibratedPressed();
    void clearPressed();
};
