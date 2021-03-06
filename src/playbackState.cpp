#include "playbackState.h"
#include "pauseRecordingState.h"
#include "pausePlaybackState.h"

PlaybackState::PlaybackState(App *a):BaseState(a){
    BaseState::initialize();
    app->path.last.x = 0;
    app->path.last.y = 0;
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
    msg += "[RETURN] para REINICIAR reproduccion";
   
    
    font->drawString(msg, 230, 20);
    
    
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
        case 13:
            app->resetData();
            break;
        default:
            break;
    }
}

void PlaybackState::changeMode(){
    
    app->setCurrentState(new PauseRecordingState(app));
    delete this;
}