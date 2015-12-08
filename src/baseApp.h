#ifndef __baseApp__
#define __baseApp__

#include "ofMain.h"
#include "BaseState.h"
#include "assets.h"
#include "ofxOsc.h"


class BaseApp
{
    
protected:
    Assets *assets;
public:
    class BaseState *current_state;
    BaseApp();
    
    void setCurrentState(BaseState *s);
    void keyPressed(ofKeyEventArgs& eventArgs);
    void update(ofEventArgs &args);
    void mousePressed(ofMouseEventArgs& eventArgs);
    
    void update();
    void draw();
    void next();
    
    Assets *getAssets();
    
    ofxJSONElement remoteData;
    bool bRemoteNewData;
    bool bRemoteError;
    
    void setRemoteData(ofBuffer data);
    void setRemoteError();
};

#endif