#include "ofMain.h"

#define SIZE 400
class Path{
    
    ofFbo *path;
    ofImage fondo;
public:
    ofPoint last;
    vector<ofPoint> data;
    
    Path(){
        path = new ofFbo();
        path->allocate(500, 500, GL_RGB);
        
        clear();
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
    }
    
    void add(int x, int y){
        if(last.x != 0 || last.y != 0){
            ofPushStyle();
            path->begin();
            ofSetColor(255, 0, 0);
            ofSetLineWidth(2);
            ofLine(last.x, SIZE - last.y, x, SIZE - y);
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
        row += data[i].x;
        row += ";";
        row += data[i].y;
        return row;
    }
    
    bool equals(int x, int y){
        return x == last.x && y == last.y;
    }
};

