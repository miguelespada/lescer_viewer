#include "pauseRecordingState.h"
#include "recordingState.h"
#include "pausePlaybackState.h"
#include "session.h"
#include "http.h"


PauseRecordingState::PauseRecordingState(App *a):BaseState(a){
    BaseState::initialize();
    osc = new OscSender();
};

PauseRecordingState::~PauseRecordingState(){
};

void PauseRecordingState::draw(){

    ofPushMatrix();
    ofPushStyle();

    ofBackground(200);

    ofSetColor(0);
    
    ofTrueTypeFont *font = Assets::getInstance()->getFont(16);
    if(!app->session->bSaved){
        ofBackground(200, 200, 150);
        font->drawString("[s] para GUARDAR session", 230, 40);
    }
    font->drawString("[c] para CALIBRAR", 230, 80);

    
    
    if(app->metadata.exercice == "Setas")
        font->drawString(ofToString(Assets::getInstance()->exerciceText(app->metadata.variation)), 230, 60);

    ofPopStyle();

    ofPopMatrix();

    app->drawData();
    app->drawConnectionInfo();
};

void PauseRecordingState::update(){
    app->bProcessData = false;
    if(app->session->bSaved)
        app->bProcessData = true;
        
};

void PauseRecordingState::next(){
    delete osc;
    app->setCurrentState(new RecordingState(app));
    delete this;
};

void PauseRecordingState::keypressed(int key){
    if(key >= '1' && key <= '9'){
        setVariation(key - '0');
    }
    switch (key) {
        case 's':
            app->dumpHeatmap();
            app->save();
            osc->sendAction("/end", 0);
        case 'c':
            app->setRotationRef();
            
            
            break;
        default:
            break;
    }
}

void PauseRecordingState::changeMode(){
    app->setCurrentState(new PausePlaybackState(app));
    delete this;
}

void PauseRecordingState::setVariation(int v){
    if(app->getVariation(v)){
        osc->sendAction("/game", v, Assets::getInstance()->exerciceCode(v), Assets::getInstance()->maxLife(v));
    }
}
