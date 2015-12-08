#include "recordingState.h"
#include "pauseRecordingState.h"
#include "pausePlaybackState.h"
#include "session.h"


RecordingState::RecordingState(App *a):BaseState(a){
    BaseState::initialize();
    app->session->bSaving = true;
};

RecordingState::~RecordingState(){
    app->session->bSaving = false;
};

void RecordingState::draw(){
    ofPushMatrix();
    ofPushStyle();
    
    ofBackground(255);
    
    ofSetColor(0);
    ofTrueTypeFont *font = Assets::getInstance()->getFont(12);
    
    string msg = "[ESPACIO] para PARAR session";
    
    font->drawString(msg, 230, 80);
    
    
    
    font = Assets::getInstance()->getFont(40);
    font->drawString("MODO: GRABAR", 230, 40);
    font = Assets::getInstance()->getFont(12);
    font->drawString("[CLICK] para cambiar de modo", 230, 60);
    
    
    ofSetColor(255, 0, 0);
    ofCircle(700, 30, 10);
    
    ofPopStyle();

    ofPopMatrix();
    
    app->drawData();
    app->drawConnectionInfo();
};

void RecordingState::update(){
    app->bProcessData = true;
};

void RecordingState::next(){
    app->setCurrentState(new PauseRecordingState(app));
    delete this;
};

void RecordingState::keypressed(int key){
    switch (key) {
        case ' ':
            next();
            break;
        case 13:
            changeMode();
            break;
            
        default:
            break;
    }
}

void RecordingState::changeMode(){
    app->setCurrentState(new PausePlaybackState(app));
    delete this;
}