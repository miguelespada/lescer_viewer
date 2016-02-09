#include "app.h"
#include "http.h"
#include "session.h"
#include "heatmap.h"

#define X 0
#define Y 1
#define Z 2

App::App():BaseApp(){
    http = new HTTP(this);
    session = new Session(this);
    
    bError = false;
    bConnected = false;
    bNewData = false;
    
    rotations[X].setColor(255, 0, 0);
    rotations[Y].setColor(0, 255, 0);
    rotations[Z].setColor(0, 0, 255);
    
    heatmap.rot_x = &rotations[X];
    heatmap.rot_y = &rotations[Y];
    currentTimeOrFruits = 0;
    
    bProcessData = true;
    
    

}

void App::clear(){
    session->clear();
    
    rotations[X].clear();
    rotations[Y].clear();
    rotations[Z].clear();
    
    path.clear();
    heatmap.clear();
    movs.clear();
    reactions.clear();
    currentTimeOrFruits = 0;
}

void App::getMetadata(){
    if(!metadata.hasData())
        http->getMetadata();
}

void App::updateMetadata(){
    if(bNewData){
        metadata.update(json_data);
        
        bNewData = false;
        bConnected = true;
        setMap();
    }
}

void App::setMap(){
    if(metadata.exercice == "Campo"){
        path.setFondo(Assets::getInstance()->campo);
    }
    else if(metadata.exercice == "Ciudad"){
        path.setFondo(Assets::getInstance()->ciudad);
    }
    else if(metadata.exercice == "Supermercado"){
        path.setFondo(Assets::getInstance()->supermercado);
    }
    else if(metadata.exercice == "Setas"){
        path.setFondo(Assets::getInstance()->setas);
    }
    
    path.w = json_data["width"].asInt();
    path.h = json_data["height"].asInt();
    path.x_0 = json_data["x"].asInt();
    path.y_0 = json_data["y"].asInt();
}

void App::updateLoadedData(){
    if(bNewData){
        metadata.update(json_data);
        bNewData = false;
        resetData();
    }
}


void App::addData(float pos_x, float pos_y, float x, float y, float z){
    
    if(rotations[X].equals(x) && rotations[Y].equals(y) && rotations[Z].equals(z) && path.equals(pos_x, pos_y)){
        return;
    }
    else{
        rotations[X].add(-x);
        rotations[Y].add(y);
        rotations[Z].add(-z);
        
        path.add(pos_x, pos_y);
        session->bNew = true;
    }
    
    session->add();
    
}

void App::drawData(){
    
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(0);
    ofTranslate(0, 120);
    ofTranslate(50, 0);
    Assets::getInstance()->wireframe_head.draw(50, 296);
    ofTranslate(0, 356);
    rotations[Z].draw();
    ofTranslate(0, 128);
    rotations[X].draw();
    ofTranslate(0, 128);
    rotations[Y].draw();

    ofPopStyle();
    ofPopMatrix();
    
    ofPushStyle();
    ofPushMatrix();
    ofNoFill();
    ofSetLineWidth(3);
    ofTranslate(ofGetWidth()-405, 400);
    ofSetColor(0);
    ofRect(0, 0, 400, 400);
    heatmap.draw();
    ofPopMatrix();
    
    if(metadata.exercice != "Setas"){
        ofPushMatrix();
        ofTranslate(ofGetWidth()-405, 0);
        ofSetColor(0);
        ofRect(0, 0, 400, 400);
        path.draw();
        ofPopMatrix();
        ofPopStyle();
        
        
        ofPushMatrix();
        ofTranslate(10, 300);
        movs.draw();
        ofPopMatrix();
    }
    else{
        ofPushMatrix();
        ofTranslate(ofGetWidth()- 390, 20);
        reactions.draw();
        ofPopMatrix();
    }

}


void App::drawConnectionInfo(){

    ofPushMatrix();
    ofPushStyle();
    ofTranslate(ofGetWidth() - 100, ofGetHeight() - 40);
    ofSetColor(0);
    
    if(bConnected)
        Assets::getInstance()->on.draw(0, 0);
    else
        Assets::getInstance()->off.draw(0, 0);
    ofPopStyle();
    ofPopMatrix();
}

void App::save(){
    if(session->getSize()> 1 && !session->bSaved){
        string s = session->toCsv();
        http->upload(s);
    }
}

void App::load(){
   http->download();
}

string App::getDataRow(int i){
    string row = "";
    row += path.getDataRow(i);
    row += ";";
    row += rotations[X].getDataRow(i);
    row += ";";
    row += rotations[Y].getDataRow(i);
    row += ";";
    row += rotations[Z].getDataRow(i);
    row += ";";
    return row;
}

void App::setRotationRef(){
    
    rotations[X].setRef();
    rotations[Y].setRef();
    rotations[Z].setRef();
}

void App::newPlaybackPosition(){
    bProcessData = false;
    session->newPosition();
}

void App::resetData(){
    session->index = 0;
    clear();
    metadata.name = json_data["patient"].asString();
    metadata.exercice = json_data["exercice"].asString();
    session->timestamp = json_data["timestamp"].asString();
    session->fromCsv(json_data["data"].asString());
    
    rotations[X].ref = json_data["ref_x"].asInt();
    rotations[Y].ref = json_data["ref_y"].asInt();
    rotations[Z].ref = json_data["ref_z"].asInt();
    
    movs.left = json_data["left_movs"].asInt();
    movs.right = json_data["right_movs"].asInt();
    reactions.setFromJson(json_data["reactions"].asString());
    setMap();
    
}

void App::addJoystickMov(float m){
    if(m < -0.1 ){
        movs.left ++;
    }
    if(m > 0.1 ){
        movs.right ++;
    }

}

void App::dumpHeatmap(){
    
    static const size_t size = 1000;
    
    heatmap_t* hm = heatmap_new(size, size);
    
    int M = 21;
    float hist[M][M];
    
    for(int i = 0; i < M; i ++){
        for(int j = 0; j < M; j ++){
            hist[i][j] = 0;
        }
    }
    
    for(int i = 1; i < session->getSize(); i ++){
        float y = ofAngleDifferenceDegrees(session->getX(i), heatmap.rot_x->ref);
        float x = ofAngleDifferenceDegrees(session->getY(i), heatmap.rot_y->ref);
        x = ofMap(x, 120, -120, 0, size);
        y = ofMap(y, 120, -120, 0, size);
        heatmap_add_point(hm, x, y);
        
        x = ofMap(x, 0, size, 0, M);
        y = ofMap(y, 0, size, 0, M);
        
        hist[(int) x][(int) y] += 1;
    }
    string str = "1;2;3;4;5;6;7;8;9;10;11;12;13;14;15;16;17;18;19;20;21";
    str += "\n";
    for(int j = 0; j < M; j ++){
        for(int i = 0; i < M; i ++){
            hist[i][j] = hist[i][j] / (float) session->getSize();
            hist[i][j] *= 100;
            str += ofToString(round(hist[i][j] * 100) / 100.0);
            if( i != M - 1)
                str += ";";
        }
        if( j != M - 1)
            str += "\n";
    }
    ofFile file(Assets::getInstance()->dataPath() + ofToString(metadata.name)+ "-" + session->timestamp + ".csv", ofFile::WriteOnly);
    file << str;
    
    
    
    
    unsigned char pixels[size*size*4];
    heatmap_render_default_to(hm, pixels);
    
    ofImage img;
    img.setFromPixels(pixels, size, size, OF_IMAGE_COLOR_ALPHA);
    img.saveImage(Assets::getInstance()->dataPath() + ofToString(metadata.name)+ "-" + session->timestamp + ".png");
    
}