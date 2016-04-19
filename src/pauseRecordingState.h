
#ifndef __pause_recording__state__
#define __pause_recording__state__

#include "baseState.h"
#include "app.h"
#include "OscSender.h"

class PauseRecordingState: public BaseState
{
    
public:
    PauseRecordingState(App *a);
    ~PauseRecordingState();
    std::string toString() { return "pause recording"; }
    void update();
    void draw();
    void next();
    void keypressed(int key);
    void changeMode();
    
    OscSender *osc;
    void setVariation(int v);
    
    void clean();
};

#endif