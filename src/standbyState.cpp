#include "standbyState.h"
#include "recordingState.h"
#include "pausePlaybackState.h"

StandbyState::StandbyState(App *a):BaseState(a){
    BaseState::initialize();
};

StandbyState::~StandbyState(){
};

void StandbyState::draw(){
    app->drawConnectionInfo();
};

void StandbyState::update(){
    if(app->bConnected)
        next();
    if(ofGetFrameNum() % 60 == 0)
        app->getMetadata();
    
    app->updateMetadata();
};

void StandbyState::next(){
    
    app->setCurrentState(new PausePlaybackState(app));
    delete this;
};


void StandbyState::keypressed(int key){
    switch (key) {
        case ' ':
            next();
            break;
        case 13:
            app->setCurrentState(new PausePlaybackState(app));
            delete this;
            break;
        default:
            break;
    }
}