
#ifndef __playback__state__
#define __playback__state__

#include "baseState.h"
#include "app.h"

class PlaybackState: public BaseState
{
    
public:
    PlaybackState(App *a);
    ~PlaybackState();
    std::string toString() { return "stand by"; }
    void update();
    void draw();
    void next();
    void keypressed(int key);
    void changeMode();
};

#endif