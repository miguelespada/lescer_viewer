

#ifndef __assets__
#define __assets__

#include "baseAssets.h"


class Assets: public BaseAssets
{
    static Assets* instance;
    Assets();

public:
    static Assets* getInstance();
    void loadAssets();
    
    bool isViewer();
    
    ofImage cabeza_x;
    ofImage cabeza_y;
    ofImage cabeza_z;
    ofImage wireframe;
    ofImage wireframe_head;
    ofImage on;
    ofImage off;
    
    ofImage rec_on;
    ofImage rec_off;
    ofImage play_on;
    ofImage play_off;
    ofImage saved;
    ofImage unsaved;
    ofImage error;
    ofImage campo;
    ofImage ciudad;
    ofImage setas;
    ofImage supermercado;
    ofImage joystick;
    
    ofVideoPlayer myVideo;
};

#endif
