#include "ofMain.h"
#include "assets.h"

class JoystickMovs{
    
public:
    int left;
    int right;
    
    JoystickMovs(){
    };
    
    void clear(){
        left = 0;
        right = 0;
    }
    
    void draw(){
        ofPushStyle();
        ofSetColor(0);
        
        ofTrueTypeFont *font = Assets::getInstance()->getFont(14);
        
        string msg;
        msg += "MOVIMIENTOS";
        msg += "\n";
        msg += "Izquierda: ";
        msg += ofToString(left);
        msg += "\n";
        msg += "Derecha: ";
        msg += ofToString(right);
        font->drawString(msg, 0, 0);
        ofPopStyle();
    }
};