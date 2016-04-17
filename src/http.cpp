#include "http.h"
#include "session.h"

HTTP::HTTP(App *a){
    app = a;
    httpUtils.start();
    ofLogNotice() << "Starting HTTP service";
}

void HTTP::getMetadata(){
    ofAddListener(httpUtils.newResponseEvent,this, &HTTP::metadataResponse);
    ofxHttpForm form;
    form.method = OFX_HTTP_GET;
    form.action = "http://localhost:3000/patients/selected.json";
    httpUtils.addForm(form);

}

bool HTTP::getVariation(int v){
    ofAddListener(httpUtils.newResponseEvent,this, &HTTP::variationResponse);
    ofxHttpForm form;
    form.method = OFX_HTTP_GET;
    form.action = "http://localhost:3000/fruit/" + ofToString(v) + ".json";
    httpUtils.addForm(form);
    bWaiting = true;
    return true;
}

void HTTP::variationResponse(ofxHttpResponse & response){
    bWaiting = false;
    if(response.reasonForStatus == "OK"){
        ofLogNotice() << "Download succesfull";
        app->bError = false;
        Assets::getInstance()->ejercicios_settings.parse(response.responseBody);
        
    }
    else{
        ofLogError() << "Download error";
        app->bError = true;
    }
    
    ofRemoveListener(httpUtils.newResponseEvent,this,&HTTP::variationResponse);
}


void HTTP::upload(string csv){
    ofAddListener(httpUtils.newResponseEvent,this, &HTTP::uploadResponse);
    ofxHttpForm form;
    form.action = "http://localhost:3000/sessions/upload.json";
    form.method = OFX_HTTP_POST;
    form.addFormField("data", csv);
    form.addFormField("timestamp", app->session->getTimeStamp());
    form.addFormField("ref_x", ofToString(app->rotations[0].ref));
    form.addFormField("ref_y", ofToString(app->rotations[1].ref));
    form.addFormField("ref_z", ofToString(app->rotations[2].ref));
    form.addFormField("left_movs", ofToString(app->movs.left));
    form.addFormField("right_movs", ofToString(app->movs.right));
    form.addFormField("reactions", ofToString(app->reactions.getDataRow()));
    form.addFormField("time", ofToString(app->ellapsedTime));
    form.addFormField("left_view", ofToString(app->lookingLeft()));
    form.addFormField("explored", ofToString(app->exploredPercent()));
    httpUtils.addForm(form);
}

void HTTP::uploadHeatmap(string heatmap){
    ofAddListener(httpUtils.newResponseEvent,this, &HTTP::uploadResponse);
    ofxHttpForm form;
    form.action = "http://localhost:3000/sessions/uploadHeatmap.json";
    form.method = OFX_HTTP_POST;
    form.addFormField("timestamp", app->session->getTimeStamp());
    form.addFormField("heatmap", heatmap);
    httpUtils.addForm(form);
}

void HTTP::download(){
    ofAddListener(httpUtils.newResponseEvent,this,&HTTP::downloadResponse);
    
    ofxHttpForm form;
    form.method = OFX_HTTP_GET;
    form.action = "http://localhost:3000/sessions/selected.json";
    httpUtils.addForm(form);
}

void HTTP::setExercice(string exercice){
    ofxHttpForm form;
    form.method = OFX_HTTP_POST;
    form.addFormField("name", exercice);
    form.action = "http://localhost:3000/exerciceByName.json";
    httpUtils.addForm(form);
}


void HTTP::downloadResponse(ofxHttpResponse & response){
    
    if(response.reasonForStatus == "OK"){
        ofLogNotice() << "Download succesfull";
        app->bError = false;
        app->json_data.parse(response.responseBody);
        
        app->bNewData = true;
        
    }
    else{
        ofLogError() << "Download error";
        app->bError = true;
    }
    
    ofRemoveListener(httpUtils.newResponseEvent,this,&HTTP::downloadResponse);
}

void HTTP::metadataResponse(ofxHttpResponse & response){

    if(response.reasonForStatus == "OK"){
        ofLogNotice() << "Get metadata succesfull";
        app->json_data.parse(response.responseBody);
        app->bNewData = true;
        app->bError = false;
    }
    else{
        ofLogError() << "Get metadata  error";
        app->bError = true;
    }
    
    ofRemoveListener(httpUtils.newResponseEvent,this,&HTTP::metadataResponse);
}


void HTTP::uploadResponse(ofxHttpResponse & response){
    if(response.reasonForStatus == "OK"){
        ofLogNotice() << "Upload succesfull";
        app->session->bSaved = true;
    }
    else{
        ofLogError() << "Upload error";
        app->session->bSaved = false;
    }
    
    ofRemoveListener(httpUtils.newResponseEvent,this,&HTTP::uploadResponse);
}