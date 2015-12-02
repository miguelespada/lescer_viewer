
#ifndef __pause_playback__state__
#define __pause_playback__state__

#include "baseState.h"
#include "app.h"

class PausePlaybackState: public BaseState
{
    
public:
    PausePlaybackState(App *a);
    ~PausePlaybackState();
    std::string toString() { return "pause playback"; }
    void update();
    void draw();
    void next();
    void keypressed(int key);
    void changeMode();
};

#endif