#include "OscAdapter.h"
#include "http.h"
#include "session.h"
#include "recordingState.h"

OscAdapter::OscAdapter(App *a){
    app = a;
    int localPort = a->getAssets()->getLocalPort();

    receiver = new ofxOscReceiver;

    receiver->setup(localPort);

    ofLogNotice() << "listening for osc messages on port " << localPort;
    bOnline = false;

    host = a->getAssets()->getRemoteIp();
    port = a->getAssets()->getRemotePort();

    cout << "Sending to "<< host << " " << port << endl;

    ofAddListener(ofEvents().update, this, &OscAdapter::update);
}

OscAdapter::~OscAdapter(){
    delete receiver;
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
    
    if(msg.getAddress() == "/pause"){
        app->current_state->next();

    }
    
    if(msg.getAddress() == "/variation"){
        app->metadata.variation = msg.getArgAsInt32(0);
    }
    
    
    if(msg.getAddress() == "/new"){
        if(app->metadata.variation == 0)
            return;
        app->clear();
        app->setCurrentState(new RecordingState(app));
        app->session->bSaving = true;
    }


    ofSetLogLevel(OF_LOG_NOTICE);


}
