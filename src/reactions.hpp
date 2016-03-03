#include "ofMain.h"

#define N_POS 8
class Reactions{
    
public:
    
    int positions[N_POS];
    float values[N_POS];
    int missed[N_POS];
    
    float total_time;
    int n_hits;
    
public:
    
    int last_pos;
    float last_time;
    
    Reactions(){
        clear();
    };
    
    void clear(){
        
        for(int i = 0; i < N_POS; i ++){
            positions[i] = 0;
            values[i] = 0;
            missed[i] = 0;
        }
        
        n_hits = 0;
        total_time  = 0;
        last_pos = 0;
        last_time = 0;
    }
    
    void add(int pos, float time){
        if(time == -1){
            missed[pos] += 1;
        }
        else {
        
            last_time = time;
            n_hits += 1;
            total_time += last_time;
            
            positions[pos] += 1;
            values[pos] += last_time;
        }
    }
    
    void draw(){
        float mean = 0;
        if(n_hits > 0)
            mean = total_time / n_hits;
        
        ofTrueTypeFont *font = Assets::getInstance()->getFont(12);
        
        ofPushStyle();
        ofPushMatrix();
        
        ofSetColor(0);
        string msg = "REACCIONES";
        msg += "\n";
        msg += "TOTAL: " + ofToString(n_hits);
        msg += "\n";
        msg += "ULTIMA: " + ofToString(last_time, 2);
        msg += "\n";
        msg += "MEDIA: " + ofToString(mean, 2);
        
        for(int i = 0; i < N_POS; i ++){
            mean = 0;
            
            if(positions[i] > 0)
                mean += values[i] / positions[i];
            
            msg += "\n";
            msg += ofToString(i)  +  "   N:   " + ofToString(positions[i], 2) +  "   MEDIA   " + ofToString(mean, 2) + " (s)" + "  MISSED : " + ofToString(missed[i], 2);
        }
        
        font->drawString(msg, 0, 0);
        
        ofPopMatrix();
        ofPopStyle();
        
    }
    
    
    string getDataRow(){
        string row = "";
        for(int i = 0; i < N_POS; i ++){
            row += ofToString(i);
            row += ";";
            row += ofToString(positions[i]);
            row += ";";
            row += ofToString(values[i]);
            row += ";";
            row += ofToString(missed[i]);
            row += ";";
        }
        return row;
    }
    
    void setFromJson(string data){
        vector<string> tokens = ofSplitString(data, ";");
        if(tokens.size() < N_POS * 4)
            return;
        n_hits = 0;
        for(int i = 0; i < N_POS; i ++){
            positions[i] = ofToInt(tokens[(i * 4) + 1]);
            n_hits += positions[i];
            values[i] = ofToFloat(tokens[(i * 4) + 2]);
            total_time += values[i];
            missed[i] = ofToInt(tokens[(i * 4) + 3]);
        }
    }
};