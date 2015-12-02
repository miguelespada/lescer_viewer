
#ifndef __pause_recording__state__
#define __pause_recording__state__

#include "baseState.h"
#include "app.h"

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
};

#endif