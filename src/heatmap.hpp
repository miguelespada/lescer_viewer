#include "ofMain.h"

#define SIZE 400


class Heatmap{
    
    ofFbo *heatmap;
    
public:
    
    Rotation *rot_x;
    Rotation *rot_y;
    int L;
    
    Heatmap(){
        heatmap = new ofFbo();
        heatmap->allocate(SIZE, SIZE, GL_RGB);
        L = 400;
    }
    
    void clear(){
        heatmap->begin();
        ofClear(220);
        ofEnableAlphaBlending();
        heatmap->end();
    };
    
    
    void draw(){
        
        ofPushStyle();
        
        clear();
        heatmap->begin();
        int size = rot_x->data.size();
        if(size > 1){
            
            int s = size;
            if(s > L)
                s = L;
                    
            for(int i = 1; i < s; i ++){
                float x = rot_y->dist(size - i);
                float y = rot_x->dist(size - i);
                
                x = ofMap(x, 120, -120, 0, SIZE);
                y = ofMap(y, 120, -120, 0, SIZE);
                
                ofSetColor(0, 50);

                ofEllipse(x, y, 5, 5);
                
            }
            
        }
        
        heatmap->end();
        
        ofSetColor(255);
        heatmap->draw(0,0);
        
        ofPopStyle();
    }
    
};

