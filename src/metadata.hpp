#include "ofxJSON.h"
class Metadata{
    
public:
    string name;
    string exercice;
    
    
    Metadata(){
        name = "";
        exercice = "";
    }
    
    void update(ofxJSONElement data){
        name = data["patient"].asString();
        exercice = data["exercice"].asString();
    }
    
    bool hasData(){
        return name != "";
    }
};