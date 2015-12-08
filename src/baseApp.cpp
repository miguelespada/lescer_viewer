#include "baseApp.h"

BaseApp::BaseApp(){
    
    ofLogNotice() << "Initializing app...";
    
    assets = (Assets *)Assets::getInstance();
    
    // Register events and actions
    ofAddListener(ofEvents().keyPressed, this, &BaseApp::keyPressed);
    ofAddListener(ofEvents().update, this, &BaseApp::update);
    ofAddListener(ofEvents().mousePressed, this, &BaseApp::mousePressed);
    
    current_state = NULL;
    
    bRemoteError = false;
    bRemoteNewData = false;
}

void BaseApp::setCurrentState(BaseState *s){
    current_state = s;
}

void BaseApp::next(){
    if(current_state)
        current_state->next();
}

void BaseApp::mousePressed(ofMouseEventArgs &eventArgs){
    current_state->click(eventArgs[0], eventArgs[1]);
}

void BaseApp::update(){
    if(current_state)
        current_state->update();
}

void BaseApp::update(ofEventArgs &args){
    update();
}

void BaseApp::keyPressed (ofKeyEventArgs& eventArgs){
    current_state->keypressed(eventArgs.key);
}

void BaseApp::draw(){
    ofPushStyle();
    ofPushMatrix();
    
    ofSetWindowShape( assets->getWidth() * assets->getScale(),  assets->getHeight() * assets->getScale());
    ofScale(assets->getScale(), assets->getScale());
    
    if(current_state)
        current_state->draw();
    ofPopMatrix();
    ofPopStyle();
}

Assets * BaseApp::getAssets(){
    return assets;
}

void BaseApp::setRemoteData(ofBuffer data){
    bRemoteError = false;
    remoteData.parse(data);
    bRemoteNewData = true;
}

void BaseApp::setRemoteError(){
    bRemoteError = true;
    bRemoteNewData = false;
}