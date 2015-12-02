#include "ofMain.h"

#define SCALE 50
#define N 200
#define TOLERANCE  0.1
class Rotation{
    
    int hist[20];
    
    ofColor color;
    
public:
    
    vector <int> data;
    float last;
    int ref;

    Rotation(){
        clear();
    };
    
    bool equals(float v){
        return abs(v - last) < TOLERANCE;
    }
    
    void setColor(int r, int g, int b){
        color = ofColor(r, g, b);
    }
    
    void clearData(){
        for(int i = 0; i < 20; i ++)
            hist[i] = 0;
        
        data.clear();
        
    }
    
    void  clear(){
        clearData();
        ref = 0;
        last = 0;
    };
    
    void draw(){
        
        ofPushMatrix();
        ofSetColor(0);
        drawAngle();
        ofTranslate(140, 0);
        
        drawGraph();
        drawInfo();
        
        ofTranslate(N + 20, 0);
        drawHistogram();
        ofPopMatrix();

    }
    

    
    void  drawGraph(){
        
        ofSetColor(0);
        ofLine(0, 0, N, 0);
        
        ofSetColor(color);
        
        if(data.size() > 1){
            
            int s = data.size();
            if(s > N)
                s = N;
            
            for(int i = 1; i < s; i ++){
                float v0 = data[ data.size() - (i + 1)];
                float v1 = data[data.size()  - i];
                
                float d0 = ofAngleDifferenceDegrees(v0, ref) / 4;
                float d1 = ofAngleDifferenceDegrees(v1, ref) / 4;
                
                ofLine(i, d0, i + 1, d1);
            }
            
        }
    };
    void drawAngle(){
        
        ofPushStyle();
        ofSetColor(50);
        ofLine(0, 0, 0, -40);
        ofPopStyle();
        
        int x = 30 * cos(ofDegToRad( last - ref - 90));
        int y = 30 * sin(ofDegToRad( last - ref - 90));
        ofSetColor(color);
        ofLine(0, 0, x, y);
        ofPopStyle();
    }
    
    void  add(float v){
        last = v;
        data.push_back(last);
        int h_x = (int)ofMap(lastDist(), -180, 180, 0, 20);
        hist[h_x] += 1;
    
    };
    
    
    
    void  drawInfo(){
        ofTrueTypeFont *font = Assets::getInstance()->getFont(12);
        
        ofPushStyle();
        ofPushMatrix();
        
        ofTranslate(0, 30);
        ofSetColor(0);
        string msg = "REF: " + ofToString(int(ref));
        font->drawString(msg, -60, font->getLineHeight() * 1.6);
        
        ofPopMatrix();
        ofPopStyle();
    }
    
    void drawHistogram(){
        
        int size = data.size();
        if(size > 1){
            ofLine(0, 0, 100, 0);
            for(int i = 0; i < 20; i++){
                if(hist[i] > size) hist[i] = 0;
                ofRect(i * 10, 0, 10, (-hist[i] / float(size)) * SCALE);
            }
        }
    }
    
    float lastDist(){
        return ofAngleDifferenceDegrees(last, ref);
    };
    
    float dist(int i){
        return ofAngleDifferenceDegrees(data[i], ref);
        
    }
    
    string getDataRow(int i){
        return ofToString(data[i]);
    }
    
    void  setRef(){
        ref = last;
        
        for(int i = 0; i < 20; i ++)
            hist[i] = 0;
    };
    

};