#include "ofMain.h"
#include "ofxHttpUtils.h"
#include "app.h"


class HTTP{
    App *app;
    ofxHttpUtils httpUtils;
public:
    HTTP(App *_app);
    void upload(string csv);
    void download();
    void getMetadata();

    void uploadResponse(ofxHttpResponse & response);
    void downloadResponse(ofxHttpResponse & response);
    void metadataResponse(ofxHttpResponse & response);
    
};
