#include "pauseRecordingState.h"
#include "recordingState.h"
#include "pausePlaybackState.h"
#include "session.h"

PauseRecordingState::PauseRecordingState(App *a):BaseState(a){
    BaseState::initialize();
};

PauseRecordingState::~PauseRecordingState(){
};

void PauseRecordingState::draw(){
    
    ofPushMatrix();
    ofPushStyle();
    
    ofBackground(220);
    
    ofSetColor(0);
    ofTrueTypeFont *font = Assets::getInstance()->getFont(12);
    
    string msg = "[ESPACIO] para CONTINUAR session";
    msg += "\n";
    msg += "[s] para GUARDAR session";
    
    font->drawString(msg, 230, 80);
    
    
    
    font = Assets::getInstance()->getFont(40);
    font->drawString("MODO: GRABAR", 230, 40);
    font = Assets::getInstance()->getFont(12);
    font->drawString("[CLICK] para cambiar de modo", 230, 60);
    
    
    ofSetColor(255, 0, 0);
    if(app->session->bSaved){
        ofSetColor(200, 255, 200);
    }
    ofCircle(700, 30, 10);
    
    ofPopStyle();
    
    ofPopMatrix();
    
    app->drawData();
    app->drawConnectionInfo();
};

void PauseRecordingState::update(){
};

void PauseRecordingState::next(){
    app->setCurrentState(new RecordingState(app));
    delete this;
};

void PauseRecordingState::keypressed(int key){
    switch (key) {
        case ' ':
            next();
            break;
        case 13:
            changeMode();
            break;
        case 's':
            ofLogNotice() << "Saving data...";
            app->save();
            break;
        default:
            break;
    }
}

void PauseRecordingState::changeMode(){
    app->setCurrentState(new PausePlaybackState(app));
    delete this;
}