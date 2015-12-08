#include "baseState.h"

BaseState::BaseState(App *a){
    timer = ofGetElapsedTimef();
    app = a;
}

void BaseState::initialize(){
    ofLogNotice() << "State: " << toString();
}

BaseState::~BaseState(){
    
}

bool BaseState::isDone(int duration){
    return (ofGetElapsedTimef() - timer) >= duration;
}

void BaseState::click(int x, int y){
        if(x > 230 && x < 630 && y > 10 && y < 40)
            changeMode();
}