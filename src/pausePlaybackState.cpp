#include "playbackState.h"
#include "recordingState.h"
#include "pausePlaybackState.h"
#include "playbackState.h"
#include "pauseRecordingState.h"

PausePlaybackState::PausePlaybackState(App *a):BaseState(a){
    BaseState::initialize();
};

PausePlaybackState::~PausePlaybackState(){
};

void PausePlaybackState::draw(){
    ofPushMatrix();
    ofPushStyle();
    
    ofBackground(220);
    
    ofSetColor(0);
    
    ofTrueTypeFont *font = Assets::getInstance()->getFont(12);
    
    string msg = "[ESPACIO] para CONTINUAR reproduccion";
    msg += "\n";
    msg += "[d] para DESCARGAR sesion";
    
    font->drawString(msg, 230, 80);
    
    
    font = Assets::getInstance()->getFont(40);
    font->drawString("MODO: REPRODUCIR", 230, 40);
    font = Assets::getInstance()->getFont(12);
    font->drawString("[CLICK] para cambiar de modo", 230, 60);
    
    ofPopStyle();
    
    ofPopMatrix();
    
    ofSetColor(127);
    Assets::getInstance()->play_off.draw(700, 30, 20, 20);
    app->drawData();
    app->drawConnectionInfo();
};

void PausePlaybackState::update(){
    app->updateLoadedData();
};

void PausePlaybackState::next(){
    app->setCurrentState(new PlaybackState(app));
    delete this;
};

void PausePlaybackState::keypressed(int key){
    switch (key) {
        case ' ':
            next();
            break;
        case 'd':
            app->load();
            break;
            
        case 13:
            changeMode();
            break;
        default:
            break;
    }
}

void PausePlaybackState::changeMode(){
    app->setCurrentState(new PauseRecordingState(app));
    delete this;
}