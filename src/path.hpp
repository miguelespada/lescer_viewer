#include "ofMain.h"

#define SIZE 400
class Path{
    
    ofFbo *path;
    ofImage fondo;
public:
    ofPoint last;
    vector<ofPoint> data;
    float w;
    float h;
    float x_0;
    float y_0;
    
    Path(){
        path = new ofFbo();
        path->allocate(500, 500, GL_RGB);
        
        clear();
        
        w = 0;
        h = 0;
        x_0 = 0;
        y_0 = 0;
    };
    
    void clear(){
        path->begin();
        if(fondo.isAllocated() ){
            ofSetColor(255);
            fondo.draw(0, 0);
        }
        else{
            ofClear(255, 0, 0);
        }
        path->end();
        last.x = 0;
        last.y = 0;
        data.clear();
    }
    
    void add(float x, float y){
        if(last.x != 0 || last.y != 0){
            ofPushStyle();
            path->begin();
            ofSetColor(255, 0, 0);
            ofSetLineWidth(2);
            
            float p_xx = ofMap(last.x, x_0, x_0 + w, 0, 500);
            float xx = ofMap(x, x_0, x_0 + w, 0, 500);
            
            float p_yy = ofMap(last.y, y_0, y_0 + h, 500, 0);
            float yy = ofMap(y, y_0, y_0 + h, 500, 0);
            
            ofLine(p_xx, p_yy, xx, yy);
            
            
            path->end();
            ofPopStyle();
        }
        
        last.x = x;
        last.y = y;
        data.push_back(last);
    }
    
    void draw(){
        ofPushStyle();
        ofSetColor(255);
        path->draw(0, 0, SIZE, SIZE);
        ofPopStyle();
    }
    
    void setFondo(ofImage _fondo){
        fondo = _fondo;
        clear();
    }
    
    string getDataRow(int i){
        string row = "";
        row += ofToString(data[i].x);
        row += ";";
        row += ofToString(data[i].y);
        return row;
    }
    
    bool equals(int x, int y){
        return x == last.x && y == last.y;
    }
};

