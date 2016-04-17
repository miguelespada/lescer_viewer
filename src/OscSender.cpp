#include "OscSender.h"
#include "assets.h"

OscSender::OscSender(){
    sender = new ofxOscSender;
    
    
    host = Assets::getInstance()->getRemoteIp();
    port = Assets::getInstance()->getRemotePort();
    
    sender->setup(host, port);
    cout << "Sending to "<< host << " " << port << endl;
    
}

OscSender::~OscSender(){
    delete sender;
}


void OscSender::sendAction(string msg, int param){
    ofxOscMessage m;
    m.setAddress(msg);
    m.addIntArg(param);
    sender->sendMessage(m);
}

void OscSender::sendAction(string msg, int param, int param2){
    ofxOscMessage m;
    m.setAddress(msg);
    m.addIntArg(param);
    m.addIntArg(param2);
    sender->sendMessage(m);
}

void OscSender::sendAction(string msg, int param, int param2, int param3){
    ofxOscMessage m;
    m.setAddress(msg);
    m.addIntArg(param);
    m.addIntArg(param2);
    m.addIntArg(param3);
    sender->sendMessage(m);
}


