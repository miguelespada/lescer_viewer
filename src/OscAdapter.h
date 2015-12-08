
#ifndef __OscAdapter__
#define __OscAdapter__

#include "ofMain.h"
#include "ofxOsc.h"
#include "app.h"


class OscAdapter{
    ofxOscReceiver *receiver;
    ofxOscSender *sender;
    App *app;
    
public:
    OscAdapter(App *a);
    
    ~OscAdapter();
    bool bOnline;
    void update(ofEventArgs &args);
    
    
    string host;
    int port;
    void sendAction(string msg, int param);
    void sendAction(string msg, int param, int param2);
    
    
    void processOscMessage(ofxOscMessage msg);
    
};


#endif 