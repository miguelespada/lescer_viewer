#include "OscAdapter.h"
#include "http.h"

OscAdapter::OscAdapter(App *a){
    app = a;
    int localPort = a->getAssets()->getLocalPort();

    receiver = new ofxOscReceiver;
    sender = new ofxOscSender;

    receiver->setup(localPort);

    ofLogNotice() << "listening for osc messages on port " << localPort;
    bOnline = false;

    host = a->getAssets()->getRemoteIp();
    port = a->getAssets()->getRemotePort();

    sender->setup(host, port);
    cout << "Sending to "<< host << " " << port << endl;

    ofAddListener(ofEvents().update, this, &OscAdapter::update);
}

OscAdapter::~OscAdapter(){
    delete receiver;
    delete sender;
}

void OscAdapter::update(ofEventArgs &args){
    if(!Assets::getInstance()->isViewer()){
        while(receiver->hasWaitingMessages()){
            bOnline = true;
            ofxOscMessage m;
            receiver->getNextMessage(&m);
            processOscMessage(m);
        }
    }
}

void OscAdapter::sendAction(string msg, int param){
    ofxOscMessage m;
    m.setAddress(msg);
    m.addIntArg(param);
    sender->sendMessage(m);
}

void OscAdapter::sendAction(string msg, int param, int param2){
    ofxOscMessage m;
    m.setAddress(msg);
    m.addIntArg(param);
    m.addIntArg(param2);
    sender->sendMessage(m);
}

void OscAdapter::sendAction(string msg, int param, int param2, int param3){
    ofxOscMessage m;
    m.setAddress(msg);
    m.addIntArg(param);
    m.addIntArg(param2);
    m.addIntArg(param3);
    sender->sendMessage(m);
}

void OscAdapter::processOscMessage(ofxOscMessage msg){
    ofSetLogLevel(OF_LOG_ERROR);
    if(msg.getAddress() == "/position"){
        if(!app->bProcessData)
            return;
        app->addData(msg.getArgAsFloat(0),
                     msg.getArgAsFloat(1),
                     msg.getArgAsFloat(2),
                     msg.getArgAsFloat(3),
                     msg.getArgAsFloat(4));

        app->addJoystickMov(msg.getArgAsFloat(5));

        string exercice = msg.getArgAsString(6);
        if(app->metadata.exercice != exercice){
            app->http->setExercice(exercice);
            app->metadata.exercice = exercice;
            app->setMap();

        }
    }


    if(msg.getAddress() == "/reaction"){
        app->reactions.add(msg.getArgAsInt32(0), msg.getArgAsFloat(1));
    }

    if(msg.getAddress() == "/currentTime" || msg.getAddress() == "/currentFruits"){
        app->currentTimeOrFruits = msg.getArgAsInt32(0);
        if(msg.getArgAsInt32(0) == 0)
            app->current_state->next();
    }


    ofSetLogLevel(OF_LOG_NOTICE);


}
