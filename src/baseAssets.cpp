#include "baseAssets.h"

BaseAssets::BaseAssets(){
    string path = ofToDataPath("settings.json");
    ofLogNotice() << "Loading settings from: " << path;
    settings.open(path);
    default_font = "ProximaNova.otf";
    ofTrueTypeFont::setGlobalDpi(72);
    clearFonts();
}

void BaseAssets::clearFonts(){
    for(int i = 0; i < MAX_FONT; i++)
        fonts[i] = NULL;
}

void BaseAssets::loadVideo(ofVideoPlayer *video, string filename){
    video->loadMovie(filename);
    ofLogNotice() << "Loading: " << filename;
    videos.push_back(video);
}

void BaseAssets::loadImage(ofImage *image, string filename){
    image->loadImage(filename);
    ofLogNotice() << "Loading: " << filename;
}

void BaseAssets::stopVideos(){
    for(vector<ofVideoPlayer*>::iterator it = videos.begin(); it != videos.end(); ++it)
        (*it)->stop();
}

Json::Value BaseAssets::getData(string key){
    return settings[key];
}

int BaseAssets::getLocalPort(){
    return getData("local_port").asInt();
}

string BaseAssets::getRemoteIp(){
    return getData("remote_ip").asString();
}

int BaseAssets::getRemotePort(){
    return getData("remote_port").asInt();
}

float BaseAssets::getScale(){
    return getData("scale").asFloat();
}

int BaseAssets::getWidth(){
    return getData("width").asInt();
}

int BaseAssets::getHeight(){
    return getData("height").asInt();
}

string BaseAssets::getRemoteDataAddress(){
    return getData("remote_data").asString();
}

void BaseAssets::loadFont(int size){
    fonts[size] = new ofTrueTypeFont();
    fonts[size]->loadFont(default_font, size);
    fonts[size]->setLetterSpacing(1.1);
    fonts[size]->setSpaceSize(0.3);
    ofLogNotice() << "Loading font: " << default_font << " " << size << " pxs";
}

ofTrueTypeFont *BaseAssets::getFont(int size){
    if(fonts[size] == NULL)
         loadFont(size);
    return fonts[size];
}

