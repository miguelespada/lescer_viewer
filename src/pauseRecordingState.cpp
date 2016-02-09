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
    
    ofBackground(200);
    
    ofSetColor(0);
    
    ofTrueTypeFont *font = Assets::getInstance()->getFont(40);
    
    string msg = "FRAMES: " + ofToString(app->session->getSize());
    
    font->drawString(msg, 230, 50);
    
    font = Assets::getInstance()->getFont(12);
    msg = "[ESPACIO] para CONTINUAR session";
    msg += "\n";
    msg += "[RETURN] para LIMPIAR session";
    msg += "\n";
    msg += "[s] para GUARDAR session";
    font->drawString(msg, 230, 80);
    
    
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
            app->clear();
            break;
        case 's':
            ofLogNotice() << "Saving data...";
            app->save();
            app->dumpHeatmap();
            break;
        default:
            break;
    }
}

void PauseRecordingState::changeMode(){
    app->setCurrentState(new PausePlaybackState(app));
    delete this;
}