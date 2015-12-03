#include "playbackState.h"
#include "pauseRecordingState.h"
#include "pausePlaybackState.h"

PlaybackState::PlaybackState(App *a):BaseState(a){
    BaseState::initialize();
};

PlaybackState::~PlaybackState(){
};

void PlaybackState::draw(){
    
    ofPushMatrix();
    ofPushStyle();
    
    ofBackground(255);
    
    ofSetColor(0);
    ofTrueTypeFont *font = Assets::getInstance()->getFont(12);
    
    string msg = "[ESPACIO] para PARAR reproduccion";
    msg += "\n";
    msg += "[x] para REINICIAR reproduccion";
   
    
    font->drawString(msg, 230, 80);
    
    
    font = Assets::getInstance()->getFont(40);
    font->drawString("MODO: REPRODUCIR", 230, 40);
    font = Assets::getInstance()->getFont(12);
    font->drawString("[CLICK] para cambiar de modo", 230, 60);
    
    
    ofPopStyle();
    
    ofPopMatrix();
    
    Assets::getInstance()->play_on.draw(700, 30, 20, 20);

    app->drawData();
    app->drawConnectionInfo();
};


void PlaybackState::update(){
    app->newPlaybackPosition();

};

void PlaybackState::next(){
    app->setCurrentState(new PausePlaybackState(app));
    delete this;
};


void PlaybackState::keypressed(int key){
    switch (key) {
        case ' ':
            next();
            break;
        case 'x':
            app->resetData();
            break;
        case 13:
            changeMode();
            break;
        default:
            break;
    }
}

void PlaybackState::changeMode(){
    
    app->setCurrentState(new PauseRecordingState(app));
    delete this;
}