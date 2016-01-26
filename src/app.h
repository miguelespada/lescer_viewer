#ifndef __App__
#define __App__

#include "baseApp.h"
#include "metadata.hpp"
#include "rotation.hpp"
#include "heatmap.hpp"
#include "path.hpp"
#include "joystick_movs.hpp"
#include "reactions.hpp"

class Session;
class HTTP;


class App: public BaseApp
{
    
public:
    
    HTTP *http;
    Metadata metadata;
    Heatmap heatmap;
    Path path;
    JoystickMovs movs;
    Reactions reactions;
    
    int currentTimeOrFruits;
    
    App();
    ~App(){};
    
    Session *session;
    
    void getMetadata();
    void updateMetadata();
    void updateLoadedData();
    void dumpHeatmap();
    
    void setMap();
    
    ofxJSONElement json_data;
    
    bool bNewData = false;
    bool bError;
    bool bConnected;
    

    Rotation rotations[3];
    void addData(float pos_x, float pos_y, float x, float y, float z);
    
    void drawData();
    void drawConnectionInfo();
    void drawSavingInfo();
    
    void save();
    void load();
    void clear();
    string getDataRow(int i);
    
    void setRotationRef();
    
    void newPlaybackPosition();
    void resetData();
    void click(int x, int y);
    
    void addJoystickMov(float m);
    
    bool bProcessData;
};


#endif
