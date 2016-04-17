
#ifndef __recording__state__
#define __recording__state__

#include "baseState.h"
#include "app.h"

class OscSender;
class RecordingState: public BaseState
{
    
public:
    RecordingState(App *a);
    ~RecordingState();
    std::string toString() { return "recording"; }
    void update();
    void draw();
    void next();
    void keypressed(int key);
    void changeMode();

    OscSender *osc;
};

#endif