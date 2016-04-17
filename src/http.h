#include "ofMain.h"
#include "ofxHttpUtils.h"
#include "app.h"


class HTTP{
    App *app;
    ofxHttpUtils httpUtils;
public:
    HTTP(App *_app);
    void upload(string csv);
    void uploadHeatmap(string heatmap);
    void download();
    void getMetadata();
    void setExercice(string exercice);

    void uploadResponse(ofxHttpResponse & response);
    void downloadResponse(ofxHttpResponse & response);
    void metadataResponse(ofxHttpResponse & response);
    
    bool getVariation(int v);
    
    void variationResponse(ofxHttpResponse & response);
    
};
