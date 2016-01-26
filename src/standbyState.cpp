#include "standbyState.h"
#include "pauseRecordingState.h"
#include "pausePlaybackState.h"
#include "assets.h"

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
    if(Assets::getInstance()->isViewer()){
        app->load();
        app->setCurrentState(new PausePlaybackState(app));
    }
    else
        app->setCurrentState(new PauseRecordingState(app));
    delete this;
};


void StandbyState::keypressed(int key){
    switch (key) {
        case ' ':
            next();
            break;
        default:
            break;
    }
}