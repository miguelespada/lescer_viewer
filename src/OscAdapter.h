
#ifndef __OscAdapter__
#define __OscAdapter__

#include "ofMain.h"
#include "ofxOsc.h"
#include "app.h"


class OscAdapter{
    ofxOscReceiver *receiver;
    App *app;
    
public:
    OscAdapter(App *a);
    
    ~OscAdapter();
    bool bOnline;
    void update(ofEventArgs &args);
    
    
    string host;
    int port;
    
    
    void processOscMessage(ofxOscMessage msg);
    
};


#endif 