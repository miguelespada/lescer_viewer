
#ifndef __OscAdapter__
#define __OscAdapter__

#include "ofMain.h"
#include "ofxOsc.h"


class OscSender{
    ofxOscSender *sender;
    
public:
    OscSender();
    
    ~OscSender();
    
    string host;
    int port;
    void sendAction(string msg, int param);
    void sendAction(string msg, int param, int param2);
    void sendAction(string msg, int param, int param2, int param3s);
    
    
};


#endif