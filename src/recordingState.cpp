#include "recordingState.h"
#include "pauseRecordingState.h"
#include "pausePlaybackState.h"
#include "session.h"
#include "OscSender.h"


RecordingState::RecordingState(App *a):BaseState(a){
    BaseState::initialize();
    app->session->bSaving = true;

    if(app->session->getSize() == 0)
        app->clear();

    osc = new OscSender();
};

RecordingState::~RecordingState(){
    app->session->bSaving = false;
};

void RecordingState::draw(){
    ofBackground(255, 200, 200);
    app->drawData();
    app->drawConnectionInfo();


    ofTrueTypeFont *font = Assets::getInstance()->getFont(16);
    if(app->metadata.exercice == "Setas")
        font->drawString(ofToString(Assets::getInstance()->exerciceText(app->metadata.variation)), 230, 60);

};

void RecordingState::update(){
    app->bProcessData = true;
    app->ellapsedTime += ofGetLastFrameTime();

    if(app->ellapsedTime >= Assets::getInstance()->maxTime(app->metadata.variation) ||
        app->reactions.n_hits >= Assets::getInstance()->maxItems(app->metadata.variation)){
        osc->sendAction("/end", 0);
        next();
    }


};

void RecordingState::next(){
    app->setCurrentState(new PauseRecordingState(app));
    delete osc;
    delete this;
};

void RecordingState::keypressed(int key){
    switch (key) {
        default:
            break;
    }
}

void RecordingState::clean(){
    cout << "CLEAN" << endl;
    osc->sendAction("/end", 0);
    next();
}

void RecordingState::changeMode(){
    app->setCurrentState(new PausePlaybackState(app));
    delete this;
}
