#include "ofApp.h"
#include "standbyState.h"
//--------------------------------------------------------------
void ofApp::setup(){

    app.setCurrentState(new StandbyState(&app));
    osc = new OscAdapter(&app);
    gui = new Gui(&app, osc);
    ofSetFrameRate(15);
    ofEnableSmoothing();
    ofSetWindowPosition(0, 0);
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(0);
    app.draw();
    gui->draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}
