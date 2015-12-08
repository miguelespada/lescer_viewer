
#ifndef __baseAssets__
#define __baseAssets__

#include "ofMain.h"
#include "ofxJSON.h"

#define MAX_FONT 128

class BaseAssets{
public:
    BaseAssets();
    void loadImage(ofImage *image, string filename);
    void loadVideo(ofVideoPlayer *video, string filename);
    void stopVideos();
    
    int getLocalPort();
    int getWidth();
    int getHeight();
    float getScale();
    string getRemoteDataAddress();
    
    string getRemoteIp();
    int getRemotePort();
    
    virtual void loadAssets()=0;
    
    ofTrueTypeFont *getFont(int size);
    void loadFont(int size);

    string default_font;
    
private:
    vector<ofVideoPlayer*> videos;
    
    Json::Value getData(string key);
    ofxJSONElement settings;
    
    void clearFonts();
    ofTrueTypeFont		*fonts[MAX_FONT];
    
};


#endif